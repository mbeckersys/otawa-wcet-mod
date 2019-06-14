/*
 *	$Id$
 *	ConfigOutput writes all processor config to output stream
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2003-08, IRIT UPS.
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
#ifndef OTAWA_CONFIGOUTPUT_H_
#define OTAWA_CONFIGOUTPUT_H_

#include <otawa/proc/Processor.h>
#include <otawa/prop/Identifier.h>
#include <elm/system/Path.h>
#include <elm/io.h>

namespace otawa {

namespace display {

class ConfigOutput;

// ConfigOutput class
class ConfigOutput: public Processor {
public:
	static Registration<ConfigOutput> reg;
	ConfigOutput(AbstractRegistration& r = reg);
	virtual void configure(const PropList& props);

	// Configuration
	static Identifier<Path> PATH;

protected:
	virtual void processWorkSpace(WorkSpace *ws);
	virtual void setup (WorkSpace *fw);

	void dump_processor(void);
	void dump_memory(void);
	void dump_caches(void);
	void dump_cache(const otawa::hard::Cache* cc);

private:
	/********
	 * METHODS
	 ********/
	void _heading(int level, const string& name, const string& anchor="");

	/********
	 * ATTRS
	 ********/
	io::Output cout;
	Path path;
};

} }	// otawa::display

#endif /* OTAWA_CONFIGOUTPUT_H_ */
