#ifndef SIMCONTEXT_H
#define SIMCONTEXT_H

#include <stack>

#include <otawa/cfg/CFG.h>

using namespace otawa;

/**
 * @brief class holding data for execution context
 **/
class SimContext {
public:
	SimContext(const string& context_name, bool do_emit=true, bool do_annotate=true) :
				name(context_name),
				emit_trace(do_emit),
				annotate_cfg(do_annotate),
				_call_pending(false), _endofbb_pending(false),
				begin_of_func(false), end_of_func(false),
				curr_bb(NULL), pre_bb(NULL), returned_cfg(NULL)
	{}

	/*********
	 * TYPES
	 *********/
	struct callstack_item_s {
		CFG* cfg;
		int  time_called;
		callstack_item_s(CFG* c, int t) : cfg(c), time_called(t) {}
	};
	typedef struct callstack_item_s callstack_item;

	/*********
	 * ATTRS
	 *********/
	string name;
	bool emit_trace;
	bool annotate_cfg;
	std::stack<callstack_item> callstack;

	// rather not for user
	bool _call_pending;
	bool _endofbb_pending;

	// for user
	bool begin_of_func;
	bool end_of_func;
	bool begin_of_bb;  ///< implies end of previous BB
	otawa::BasicBlock* curr_bb;
	otawa::BasicBlock* pre_bb;

	int time_bb_enter;
	int time_fun_enter;

	// filled when end_of_func==true
	CFG* returned_cfg;
	int  duration_returned_cfg;
};

#endif /* SIMCONTEXT_H */
