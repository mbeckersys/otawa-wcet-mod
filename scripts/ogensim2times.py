#!/usr/bin/python

# this file parses a trace from (a modified) ogensim, and prints
# execution times of all functions that were called, as well as
# execution counts for a user-defined list of instructions (if given).
#
# (C) 2019 Martin Becker <becker@rcs.ei.tum.de>

import os
import argparse
import pprint
import time
import shlex
import subprocess
import re
import simtrace


def load_symbols(elf):
    """query nm for symbol addresses"""
    assert os.path.exists(elf), "ELF file not found (needed for symbol map)"
    # --
    symbol_map = {}
    re_sym = re.compile(r"([0-9a-fA-F]+)[\s\t]+(.)[\s\t+](\w+)")
    proc = subprocess.Popen(['arm-none-eabi-nm', '-C', elf], stdout=subprocess.PIPE, bufsize=-1)
    for line in iter(proc.stdout.readline, ''):
        match = re_sym.match(line.rstrip())
        if match:
            decaddr = int(match.group(1), 16)
            typ = match.group(2)
            name = match.group(3)
            if typ.lower() in ('t', 'u', 'v', 'w'):
                if decaddr in symbol_map:
                    print "WARN: Symbol at {:x} already has a name: {}. Updating to {}.".\
                        format(decaddr, symbol_map[decaddr], name)
                    # the latest is better.
                symbol_map[decaddr] = name
    print "Loaded {} symbols.".format(len(symbol_map))
    return symbol_map


def run_simul(sim_args, elf, sim):
    """run simulation and simultaneously parse the trace"""
    raise NotImplementedError("TODO")

    def del_arg(flag):
        """remove given flag and arg, if present"""
        for c in xrange(len(cmd_split)):
            if cmd_split[c].startswith(flag):
                if len(cmd_split[c]) == 2:
                    del cmd_split[c:c + 2]  # flag and value are separate
                else:
                    del cmd_split[c]  # flag and value are together
                print "Removed cmdline flag ({}) for simulavr".format(flag)
                return

    cmd = 'simulavr ' + sim_args
    cmd_split = shlex.split(cmd)
    # override flags that the user may have given
    del_arg('-t')
    del_arg('-f')
    cmd_split.extend(['-t', 'stdout'])  # set trace to stdout
    cmd_split.extend(['-f', elf])  # set same ELF that we are using

    print "Running Simulator: {}".format(' '.join(cmd_split))
    process = subprocess.Popen(cmd_split, bufsize=-1, stdout=subprocess.PIPE)
    while True:
        output = process.stdout.readline()
        if output == '' and process.poll() is not None:
            break
        if output:
            if not sim.consume_line(output):
                break
    return 0


def do_work(args):
    """either run simulation now, or inspect trace post-mortem"""
    sim = simtrace.SimTracer("ogensim", list_calls=args.list_calls,
                             full_stats=args.full_stats, maxcycles=args.max_cycles)
    symbmap = load_symbols(args.elf)
    sim.set_watchpoints(args.watchfile)
    sim.set_symbolmap(symbmap)

    if args.below is not None:
        sim.set_filter(args.below, True)
        print "Only code in function {} and below...".format(args.below)

    ############
    # EAT TRACE
    ############
    if args.simulate:
        print "Running Simulator live..."
        if args.trace:
            print "Tracefile ignored"
        ret = run_simul(args.simulate, args.elf, sim)
    else:
        print "Parsing trace post-mortem..."
        ret = sim.parse_trace(args.trace)

    ############
    # PRINT
    ############
    if 0 == ret:
        calls = sim.get_calls()
        if not calls:
            print "ERROR: no calls detected"
        else:
            if args.only_function:
                if args.only_function in calls:
                    if args.pretty:
                        pprint.pprint(calls[args.only_function])
                    else:
                        print calls[args.only_function]
                else:
                    print "ERROR: function \"{}\" not found in trace".format(args.only_function)
                    print "ERROR: only these available: {}".format(calls.keys())
                    return 1
            else:
                if args.pretty:
                    pprint.pprint(calls)
                else:
                    print str(calls)
            if args.coverage:
                sim.print_coverage()
        if args.watchfile:
            sim.print_watchpoints()
        print "Total cycles: {}".format(sim.total_cycles())
    return ret


def main():
    parser = argparse.ArgumentParser(description="Extract timing from ogensim trace")
    parser.add_argument('-t', '--trace', default='trace',
                        help='trace file to read')
    parser.add_argument('-m', '--max-cycles', default=0,
                        help='abort when number of simulated cycles reached')
    parser.add_argument('-e', '--elf', required=True,
                        help='ELF file to simulate')
    parser.add_argument('-s', '--simulate', default=None,
                        help='run simulator with extra arguments and parse simultaneously')
    parser.add_argument('-o', '--only-function', default=None,
                        help='only show result for specific function')
    parser.add_argument('-b', '--below', default=None,
                        help='only consider code including and below (called by) given function')
    parser.add_argument('-w', '--watchfile', default=None,
                        help='provide statistics for particular addresses given in file')
    parser.add_argument('-c', '--list-calls', action='store_true', default=False,
                        help='show calls')
    parser.add_argument('-p', '--pretty', action='store_true', default=False,
                        help='pretty-print the results with indentation')
    parser.add_argument('-g', '--coverage', action='store_true', default=False,
                        help='show number of cycles spend in each function (includes children)')
    parser.add_argument('-f', '--full-stats', action='store_true', default=False,
                        help='keep execution time of every invocation, not just min/max')
    args = parser.parse_args()

    if args.simulate:
        if (args.simulate.startswith('"') and args.simulate.endswith('"')) or \
                (args.simulate.startswith("'") and args.simulate.endswith("'")):
            args.simulate = args.simulate[1:-1]

    # get list of instructions to be watched (when and how often do they execute)
    t0 = time.time()
    ret = do_work(args)
    t1 = time.time()
    print "Total time: {:.1f}s".format(t1 - t0)
    exit(ret)


if __name__ == "__main__":
    main()
