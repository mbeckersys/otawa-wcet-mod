#ifndef _DEBUG_H_
#define _DEBUG_H_



#ifndef NDEBUG
//#define TRACE(x) x
#define TRACE(x)

extern int debugVerbose;
#define __SOURCE_INFO__ "[" << __FILE__ << ":" << __LINE__ << "] "
#define TRACE2(x) { if(debugVerbose >= 2) { x } }
#define TRACE10(x) { if(debugVerbose >= 10) { x } }
#define TRACEX(dbgL, x) { if(debugVerbose >= dbgL) { x } }



#endif //NDEBUG
#endif //_DEBUG_H_
