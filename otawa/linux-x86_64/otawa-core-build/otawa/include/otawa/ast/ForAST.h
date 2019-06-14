/*
 *	ForAST class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2003, IRIT UPS.
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
#ifndef OTAWA_AST_FOR_AST_H
#define OTAWA_AST_FOR_AST_H

#include <otawa/ast/AST.h>

namespace otawa { namespace ast {

// ForAST class
class ForAST: public AST {
	AST *bod, *cnd, *init, *inc;
protected:
	virtual ~ForAST(void);
public:
	ForAST(AST *initialization, AST *condition, AST *incrementation, AST *body);
	inline AST *initialization(void) const { return init; };
	inline AST *condition(void) const { return cnd; };
	inline AST *incrementation(void) const { return inc; };
	inline AST *body(void) const { return bod; };
	
	// AST overload
	virtual Inst *first(void);
	virtual ast_kind_t kind(void) const { return AST_For; };
	virtual ForAST *toFor(void) { return this; };
	virtual int countInstructions(void) const;
};
	
} }	// otawa::ast

#endif // OTAWA_AST_FOR_H