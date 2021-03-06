/*
 *	$Id$
 *	SilentFeature class interface
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
#ifndef OTAWA_PROC_SILENTFEATURE_H_
#define OTAWA_PROC_SILENTFEATURE_H_

#include <otawa/proc/AbstractFeature.h>

namespace otawa {

using namespace elm;

// SilentFeature class
class SilentFeature: public AbstractFeature {
public:

	template <class C>
	class Maker: public AbstractMaker {
	public:
		virtual Processor *make(void) const { return new C(); }	
	};

	inline SilentFeature(cstring name, const AbstractMaker& maker): AbstractFeature(name), _maker(maker) { }
	virtual void process(WorkSpace *fw, const PropList& props = PropList::EMPTY) const;
	virtual void check(otawa::WorkSpace*) const { }
	virtual void clean(otawa::WorkSpace*) const { }

private:
	 const AbstractMaker& _maker;
};
	
} // otawa

#endif /* OTAWA_PROC_SILENTFEATURE_H_ */
