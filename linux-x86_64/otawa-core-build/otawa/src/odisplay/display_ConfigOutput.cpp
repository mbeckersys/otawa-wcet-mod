/*
 *	$Id$
 *	display::ConfigOutput class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/system/System.h>
#include <otawa/ipet.h>
#include <otawa/display/ConfigOutput.h>
#include <otawa/hard/Processor.h>
#include <otawa/hard/Memory.h>
#include <otawa/hard/CacheConfiguration.h>

namespace otawa { namespace display {

/**
 * @class ConfigOutput
 * This processor may be used to generate an HTML output of the platform config.
 *
 * @par Require Features
 * @li @ref otawa::ILP_SYSTEM_FEATURE
 *
 * @par Configuration
 * @li @ref ConfigOutput::PATH
 */

Registration<ConfigOutput> ConfigOutput::reg(
	"otawa::display::ConfigOutput", Version(1, 0, 0),
    //provide(CONFIG_OUTPUT_FEATURE);
	p::require,	&otawa::hard::PROCESSOR_FEATURE,
    p::require,	&otawa::hard::MEMORY_FEATURE,
    p::require,	&otawa::hard::CACHE_CONFIGURATION_FEATURE,
	p::end
);


/**
 */
ConfigOutput::ConfigOutput(AbstractRegistration& r)
: Processor(r) {
}


/**
 * Configuration identifier for @ref ConfigOutput.
 * Used to select the path of the HTML file to output to.
 * As a default, the created file is TASK_NAME-config.html
 */
Identifier<Path> ConfigOutput::PATH("", "");


/**
 */
void ConfigOutput::configure(const PropList& props) {
	Processor::configure(props);
	path = PATH(props);
}


/**
 */
void ConfigOutput::setup(WorkSpace *fw) {


}

void ConfigOutput::_heading(int level, const string& title, const string& anchor) {
	cout << "<h" << level << "><a name=\"__" << anchor << "\">" << title << "</a></h" << level << ">\n";
}

void ConfigOutput::dump_cache(const otawa::hard::Cache* cc) {
	cout << "<ul>" << endl;
	cout << "<li>policy=" << cc->replacementPolicy() << "</li>" << endl;
	cout << "<li>total size=" << cc->cacheSize() << "</li>" << endl;
	cout << "<li>blocks=" << cc->blockCount() << "</li>" << endl;
	cout << "<li>block size=" << cc->blockSize() << "</li>" << endl;
	cout << "<li>sets=" << cc->setCount() << "</li>" << endl;
	cout << "<li>assoc=" << cc->wayCount() << "</li>" << endl;
	cout << "<li>miss penalty=" << cc->missPenalty() << "</li>" << endl;
	if (cc->nextLevel()) {
		cout << "<li>next level</li>" << endl;
		dump_cache(cc->nextLevel());
	}
	cout << "</ul>" << endl;
}

void ConfigOutput::dump_caches(void) {
	// caches
	_heading(2, "Caches", "a_cache");
	const hard::CacheConfiguration *cc = otawa::hard::CACHE_CONFIGURATION(workspace());
	if (cc) {
		_heading(3, "I-Cache", "a_icache");
		if (cc->hasInstCache()) {
			const otawa::hard::Cache* icc = cc->instCache();
			const string cname = cc->cacheName(icc).chars();
			cout << cname << endl;
			dump_cache(icc);
		} else {
			cout << "None" << endl;
		}
		_heading(3, "D-Cache", "a_dcache");
		if (cc->hasDataCache()) {
			const otawa::hard::Cache* dcc = cc->dataCache();
			const string cname = cc->cacheName(dcc).chars();
			cout << cname << endl;
			dump_cache(dcc);
		} else {
			cout << "None" << endl;
		}
	}

}

void ConfigOutput::dump_processor(void) {
	_heading(2, "Processor", "a_proc");
	const hard::Processor *cproc = otawa::hard::PROCESSOR(workspace());
	if (cproc) {
		cout << "<ul>\n";
			cout << "<li>Model=" << cproc->getModel() << "</li>" << endl;
			cout << "<li>Name=" << cproc->name() << "</li>" << endl;
			cout << "<li>Arch=" << cproc->getArch() << "</li>" << endl;
			cout << "<li>Builder=" << cproc->getBuilder() << "</li>" << endl;
			cout << "<li>Stages</li><ul>" << endl;
			const Table<otawa::hard::Stage*>& stages = cproc->getStages();
			if (stages.size() > 0) {
				cout << "<li>" << stages.size() << "</li>" << endl;
				#if 0
				for(Table<const otawa::hard::Stage*>::Iterator it(stages); it; ++it) {
					cout << "<li>" <<  it->name() << "</li>" << endl;
				}
				#endif
			} else {
				cout << "<li>None</li>" << endl;
			}
			cout << "</ul>";
		cout << "</ul>\n";
	} else {
		cout << "NONE" << endl;
	}
}

void ConfigOutput::dump_memory(void) {

	_heading(2, "Memory", "a_mem");
	const hard::Memory *cmem = otawa::hard::MEMORY(workspace());

	_heading(3, "Banks");
	const Table<const otawa::hard::Bank*> & banks = cmem->banks();
	if (banks.size() > 0) {
		cout << "<ul>\n";
		for(Table<const otawa::hard::Bank*>::Iterator it(banks); it; ++it) {
			cout << "<li>bank '" << it->name() << "'</li><ul>"
				 << "<li>size=" << it->size() << " B</li>"
				 << "<li>latency=" << it->latency() << "</li>"
				 << "<li>cached=" << it->isCached() << "</li>"
				 << "</ul>" << endl;
		}
		cout << "</ul>" << endl;
	} else {
		cout << "No banks" << endl;
	}

	_heading(3, "Buses");
	const Table<const otawa::hard::Bus*> & buses = cmem->buses();
	if (buses.size() > 0) {
		cout << "<ul>\n";
		for(Table<const otawa::hard::Bus*>::Iterator it(buses); it; ++it) {
			cout << "<li>bus '" << it->name() << "'</li><ul>" << endl;
		}
		cout << "</ul>" << endl;
	} else {
		cout << "No buses" << endl;
	}
}

/**
 */
void ConfigOutput::processWorkSpace(WorkSpace *ws) {

	if(!path)
		path = _ << ENTRY_CFG(ws)->label() << "-config.html";
	io::OutStream *file;
	try {
		file = elm::system::System::createFile(path);
	}
	catch(elm::system::SystemException& exn) {
		throw new ProcessorException(*this, _ << "cannot create file \"" << path << "\": " << exn.message());
	}
	cout.setStream(*file);

	// header
	cout << "<html>\n\t<head>\n\t\t<title>Platform Configuration"
		 << " (" << ws->process()->program()->name() << ")</title>\n\t</head>\n\t<body>\n"
		 << "\t\t<h1>Platform Configuration</h1>\n"
			"\t\t\t<ul>\n"
			"\t\t\t\t<li><a href=\"#__a_proc\">Processor</a></li>\n"
			"\t\t\t\t<li><a href=\"#__a_mem\">Memory</a></li>\n"
			"\t\t\t\t<li><a href=\"#__a_cache\">Caches</a></li>\n"
		 << "\t\t</ul>\n";

	dump_processor();
	dump_memory();
	dump_caches();

	// tail
	cout << "\t<center><i>Generated by <a href=\"http://www.otawa.fr\">OTAWA</a> (c) 2008, IRIT - UPS</center>\n"
		 << "\t</body>\n</html>\n";

}

//p::feature CONFIG_OUTPUT_FEATURE("otawa::CONFIG_OUTPUT_FEATURE", true);

} } // otawa::display
