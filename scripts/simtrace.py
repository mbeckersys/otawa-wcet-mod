# Various functions to run a cycle-accurate simulator and parse the trace
#
# this file parses a trace from (a modified) ogensim, and prints
# execution times of all functions that were called, as well as
# execution counts for a user-defined list of instructions (if given).
#
# (C) 2019 Martin Becker <becker@rcs.ei.tum.de>
import traceback
import sys
import time
import pprint


class SimTracer(object):
    """Parse simulator trace"""

    def __init__(self, name, list_calls=False, full_stats=False, maxcycles=0):
        # settings:
        self.name = name
        self.below = None
        self.pretty = True
        self.list_calls = list_calls
        self.full_stats = full_stats
        self.maxcycles = int(maxcycles)
        # data:
        self.calls = dict()  # dict of dicts: {'name', 'bcet', 'wcet', 'lastcall', 'running'}
        self.covdata = {}
        self.symbol_map = {}
        self.current_cycle = 0
        self.start_cycle = None
        self.stack = list()  # tuple (function, call time)
        self.wlist = dict()  # decimal address => { 'BBname', 'is_begin'}
        self.wstat = dict()  # BBname => {'count': how_often_visited , 'laststart':
        # when_visited_last  'running': is_still_in_block, 'bcet', 'wcet','sum','sum-self',
        # 'wcet-self','bcet-self','et' }
        self.delayed_addr = None
        self.pending_return = False
        self.pending_call = False
        self.next_show = 0
        self.last_shown_cycle = 0

    def set_symbolmap(self, smap):
        self.symbol_map = smap

    def set_filter(self, fname, below=True):
        if below:
            self.below = fname

    def get_calls(self):
        return self.calls

    def _get_symbol(self, addr):
        """return name of symbol at address, or return address if not known"""
        return self.symbol_map.get(addr, hex(addr))

    def _register_broken(self, fun):
        """
        Calling this marks the timing of the function unknown, due to some unexpected call/ret
        """
        try:
            self.calls[fun]['valid'] = False
        except KeyError:
            pass

    def _get_stack(self):
        """return current function stack as string"""
        try:
            # try to find main
            i0 = (e for e, t in enumerate(self.stack) if t[0] == "main").next()
        except StopIteration:
            i0 = 0
        return "=>".join([f[0] for f in self.stack[i0:]])

    def _register_call(self, addr, cycle):
        """
        A function was called at given cycle. This is called *after* the call insn finished.
        fun is the address of the first insn after the call, i.e., the callee.
        """
        # --
        fun = self._get_symbol(addr)
        if self.below is None or fun == self.below or self._is_below_function(self.below):
            if fun not in self.calls:
                # empty data dict for this fcn
                self.calls[fun] = {'bcet': sys.maxint, 'wcet': 0, 'et': [], 'lastcall': cycle,
                                   'count': 0, 'valid': True, 'fun': fun, 'total': 0,
                                   'total-self': 0}
            self.calls[fun]['count'] = self.calls[fun]['count'] + 1
            self.calls[fun]['lastcall'] = cycle
            self.calls[fun]['treturnedto'] = cycle

            # maintain caller's stats
            if self.stack:
                caller = self.stack[-1][0]
                if caller in self.calls:
                    inc = cycle - self.calls[caller]['treturnedto']  # time of insn since last
                    # callee ret
                    self.calls[caller]['total-self'] += inc

        self.stack.append((fun, cycle))
        if self.list_calls:
            print "{} called @{}. stack={}".format(fun, cycle, self._get_stack())

    def _register_ret(self, cycle):
        """
        A function returned at the given cycle. This is called *after* the return finished.
        next_addr is the address of the first insn after the return, i.e., the returnee.
        """
        fun, callcycle = self.stack.pop()

        # maintain profile of callee
        if self.below is None or fun == self.below or self._is_below_function(self.below):

            #############################
            # maintain profile of caller
            #############################
            if self.stack:
                caller = self.stack[-1][0]
                if caller in self.calls:
                    self.calls[caller]['treturnedto'] = cycle

            ################################
            # maintain profile of returning
            ################################

            if fun not in self.calls:
                print "WARN @" + str(cycle) + ": RET of " + fun + ", but have seen no call"
                self._register_broken(fun)
                return

            self.calls[fun]['running'] = False

            # time incl callees:
            et = cycle - callcycle
            if et > self.calls[fun]['wcet']:
                self.calls[fun]['wcet'] = et
            if et < self.calls[fun]['bcet']:
                self.calls[fun]['bcet'] = et
            self.calls[fun]['total'] += et
            if self.full_stats:
                self.calls[fun]['et'].append(et)

            # self time:
            et = cycle - self.calls[fun]['treturnedto']
            self.calls[fun]['total-self'] += et

        if self.list_calls:
            print "{} returns at @{}. stack={}".format(fun, cycle, self._get_stack())

    def _register_visit(self, titl, is_begin, cycle):
        """
        register a watchpoint that was visited
        """
        current = self.wstat[titl]
        if is_begin:
            # BB starts
            if current["is_running"]:
                # print "WARN: watchpoint " + titl + " @" + str(cycle) +\
                #     " starts before it ended. Last visit=" + str(current["last_begin"])
                pass  # that is a normal case, when no end addr is given
            current["is_running"] = True
            current["last_begin"] = cycle
            current["count"] += 1
        else:
            # BB ends
            if not current["is_running"]:
                print "WARN: watchpoint " + titl + " @" + str(cycle) + \
                    " ends before it started. Last visit=" + str(current["last_begin"])
            else:
                duration = cycle - current["last_begin"]
                current["sum"] += duration
                current["is_running"] = False
                if current["bcet"] > duration:
                    current["bcet"] = duration
                if current["wcet"] < duration:
                    current["wcet"] = duration
        # finally...update
        self.wstat[titl] = current

    def _is_below_function(self, fname):
        """Check whether current execution is in callstack below (=within callees) of fname,
        or within fname itself"""
        # --
        if fname is None or not self.stack:
            return True
        try:
            # FIXME: only re-iterate if stack has changed.
            _ = next(f for f, t in self.stack if f == fname)
            return True
        except StopIteration:
            return False

    def consume_line(self, line, show_progress=True):
        """
        parses a line of simulator's trace file, and keeps track of function calls and times.

        :return true if end reached
        """
        # parse line
        # create dict of function names and min/max execution times on the fly

        # <elfname> <PC>: [event:] <cycle>: <function>(+<offset>)? <asm>
        # offset is number of instructions, whereas one instruction is assumed 2Bytes
        # (though some are 4 bytes...)
        # XXX: function *is not necessarily* the current function! Sometimes another label
        # is used to compute offset. Therefore we need a symbol map

        #################
        # Parse fun
        #################
        line = line.rstrip()
        parts = line.split(None)  # split at any whitespace
        if len(parts) < 5:
            return True

        try:
            p = 0
            elfname = parts[p].strip()
            p += 1
            hexaddr = parts[p].rstrip(":")
            decaddr = int(hexaddr, 16)
            p += 1
            # optional event specifier
            evtest = parts[p].strip().strip(":")
            if evtest.isalpha():
                event = evtest
                p +=1
            current_cycle = int(parts[p].strip()[0:-1])
            p += 1
            self.current_cycle = current_cycle
            if self.start_cycle is None:
                self.start_cycle = current_cycle
            unreliable_fun = parts[p].strip() # Label/Offset sometimes is based on other func in avr
            p += 1
            asm = parts[p].strip()
            p += 1
            op = parts[p].strip() if len(parts) > 5 else None
        except:
            print "Skipping trace line: {}".format(line)
            return True

        #################
        # "Progress bar"
        #################
        if show_progress:
            now = time.time()
            if now > self.next_show:
                cps = current_cycle - self.last_shown_cycle
                self.last_shown_cycle = current_cycle
                print "Cycles: {:,} ({:,} per second), stack={}".format(current_cycle, cps,
                                                                        self._get_stack())
                self.next_show = now + 1.0

        if asm == "CPU-waitstate":
            return True

        #################
        # log watchpoints
        #################
        if self.below is None or self._is_below_function(self.below):
            # register end of watchpoint
            if self.delayed_addr:
                self._register_visit(self.delayed_addr, False, current_cycle)
                self.delayed_addr = None

            # watchlist
            if decaddr in self.wlist:
                if self.wlist[decaddr]["is_begin"]:
                    self._register_visit(self.wlist[decaddr]["name"], True, current_cycle)
                if self.wlist[decaddr]["is_end"]:
                    # here we do a trick: we want to include the time of the jump to the next BB...
                    # so we have to register the end in the NEXT non-wait-cycle
                    # we could do the following, if the jump shall NOT count:
                    self.delayed_addr = self.wlist[decaddr]["name"]

        # this is only reached by no-wait-states instructions
        if self.pending_call:
            self._register_call(decaddr, current_cycle)  # time to do the call is attributed to the
            # caller
            self.pending_call = False
        elif self.pending_return:
            self._register_ret(current_cycle)  # time for the return is attributed to the callee
            self.pending_return = False

        if 'RETURN' in line:
            pass
        self.pending_return = asm in ("RET", "RETI") or line.endswith(";; RETURN")
        self.pending_call = asm in ("ICALL", "CALL", "RCALL") or line.endswith(";; CALL")
        if self.pending_call:
            # we must ignore call to next instruction, since this is actually a trick to find
            # the addr of the next instruction in the code, and the stack return address is
            # immediately popped
            try:
                if int(op, 16) == decaddr + 2:
                    # print "Ignoring (r)call .+0 @{}".format(current_cycle)
                    self.pending_call = False
            except ValueError:
                pass  # could be "RCALL Z"

        if 0 < self.maxcycles < self.total_cycles():
            print "max cycles reached."
            return False
        return True

    def total_cycles(self):
        """total number of seen cycles"""
        return self.current_cycle - self.start_cycle

    def print_watchpoints(self):
        if len(self.wlist) > 0:
            pprint.pprint(self.wstat)

    def print_coverage(self):
        if self.below is None:
            total_cyc = self.total_cycles()
        else:
            assert self.below in self.calls, "Something went wrong. No data below {}".format(
                self.below)
            total_cyc = self.calls[self.below]['total']

        cov = []
        for _, func in self.symbol_map.iteritems():
            if func in self.calls:
                cycles = self.calls[func]['total']
                calls = self.calls[func]['count']
            else:
                cycles = 0
                calls = 0
            perc = (100. * cycles) / total_cyc
            cov.append((func, cycles, calls, perc))

        sorted_by_cycles = sorted(cov, key=lambda x: x[1], reverse=True)

        print "Coverage by cycles:"
        if self.pretty:
            print "{:<35}   {:>10}   {:>10}   {}".format("function", "cycles", "calls", "percent")
            for entry in sorted_by_cycles:
                print "{:<35}   {:>10,}   {:>10,}   {:>04.2f}%".format(entry[0], entry[1],
                                                                       entry[2], entry[3])
        else:
            print str(sorted_by_cycles)

    def parse_trace(self, tfile):
        """
        parse trace post-mortem. Convenience wrapper for repeated calls to consume_line().
        """
        try:
            l = 0
            with open(tfile, 'rb') as f:
                for line in f:
                    l += 1
                    if not self.consume_line(line):
                        break
            print "Parsed {} lines".format(l)
        except:
            print "File " + tfile + " could not be processed", sys.exc_info()[0]
            print(traceback.format_exc())
            return 1
        return 0

    def set_watchpoints(self, wfile):
        """
        Read a file describing watchpoints, and put them into dictionary 'wlist'
        """
        if not wfile:
            return

        try:
            with open(wfile, 'rb') as f:
                for line in f:
                    if line.startswith("#"):
                        continue
                    parts = line.split(None)  # split at any whitespace
                    hexaddr_begin = parts[0].strip()
                    decaddr_begin = int(hexaddr_begin, 16)  # hex string addr of watchpoint
                    if len(parts) > 1:
                        titl = parts[1].strip()  # readable name
                    else:
                        titl = ''

                    # add watchpoint for begin of BB
                    is_single_step = True
                    if len(parts) > 2:
                        # add another watchpoint for end of BB, if we have an end address
                        hexaddr_end = parts[2].strip()
                        decaddr_end = int(hexaddr_end, 16)  # hex string addr of watchpoint
                        if decaddr_end != decaddr_begin:
                            is_single_step = False
                            self.wlist[decaddr_end] = {'name': titl,
                                                       'is_begin': False,
                                                       'is_end': True}
                    self.wlist[decaddr_begin] = {'name': titl,
                                                 'is_begin': True,
                                                 'is_end': is_single_step}

                    # prepare wstats; this holds the visiting statistics in the end
                    self.wstat[titl] = {"addr": hexaddr_begin, "count": 0, "last_begin": -1,
                                        'bcet': sys.maxint, 'wcet': 0, 'sum': 0,
                                        'is_running': False}
        except:
            print "File " + wfile + " cound not be fully processed", sys.exc_info()[0]
            # return

        readable_list = [" " + hex(k) + " = " + v["name"] for k, v in self.wlist.iteritems()]
        print 'Watchpoints (' + str(len(readable_list)) + "):"
        print "\n".join(readable_list)
        return
