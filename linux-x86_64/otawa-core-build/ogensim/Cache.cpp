#include "Fetch.h"
#include "GenericState.h"
#include "debug.h"

// TODO: wrap hwcache

namespace otawa { namespace gensim {

Cache::Cache(sc_module_name name) {
	SC_METHOD(action);
	sensitive << in_clock.pos();
}

void Cache::action() {
    elm::cout << "cache access";
}

} } // otawa::gensim
