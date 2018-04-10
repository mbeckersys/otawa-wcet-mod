/*
 *	$Id$
 *	This file describes the "MUST" cache problem.
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2007, IRIT UPS.
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
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *	02110-1301  USA
 */

#ifndef CACHE_MUSTPROBLEM_H_
#define CACHE_MUSTPROBLEM_H_

#include <otawa/util/HalfAbsInt.h>
#include <elm/assert.h>
#include <elm/io.h>
#include <otawa/prog/WorkSpace.h>
#include <otawa/cache/LBlockSet.h>
#include <otawa/hard/Cache.h>
#include <otawa/cfg/BasicBlock.h>


namespace otawa {


class MUSTProblem {

	// Types
	public:

	class Domain {
			int A, size;

			public:
					/**
			 * @class Result
			 *
			 * Class to hold the results (for each basic block) of the abstract interpretation.
			 * @param A associativity.
			 * @param size number of conflicting L-blocks for cache line where this L-blockset goes
			 */


			inline Domain(const int _size, const int _A)
			: A (_A), size(_size)
			{
				age = new int [size];
				for (int i = 0; i < size; i++)
					age[i] = 0;
			}

			inline ~Domain() {
				delete [] age;
			}

			inline Domain(const Domain &source) : A(source.A), size(source.size) {
				age = new int [size];
				for (int i = 0; i < size; i++)
					age[i] = source.age[i];

			}

			inline Domain& operator=(const Domain &src) {
				ASSERT((A == src.A) && (size == src.size));
				for (int i = 0; i < size ; i++)
					age[i] = src.age[i];
				return(*this);

			}

			inline void glb(const Domain &dom) {
				ASSERT((A == dom.A) && (size == dom.size));

				for (int i = 0; i < size; i++) {
					if (((age[i] > dom.age[i]) && (dom.age[i] != -1)) || (age[i] == -1))
						age[i] = dom.age[i];
				}
			}

			/**
			 * @brief join two abstract cache states (merge dom into this)
			 */
			inline void lub(const Domain &dom) {
				ASSERT((A == dom.A) && (size == dom.size));

				for (int i = 0; i < size; i++) {
					// take max age of both (-1 signals "evicted")
					if (((age[i] < dom.age[i]) && (age[i] != -1))|| (dom.age[i] == -1))
						age[i] = dom.age[i];
				}
			}

			inline int getSize(void) {
				return size;
			}

			/**
			 * @brief increment age of element 'id' by 'damage'
			 */
			inline void addDamage(const int id, const int damage) {
				ASSERT((id >= 0) && (id < size));
				if (age[id] == -1)
					return;
				age[id] += damage;
				if (age[id] >= A)
					age[id] = -1;
			}

			inline bool equals(const Domain &dom) const {
				ASSERT((A == dom.A) && (size == dom.size));
				for (int i = 0; i < size; i++)
					if (age[i] != dom.age[i])
						return false;
				return true;
			}

			inline void empty() {
				for (int i = 0; i < size; i++)
					age[i] = -1;

			}

			inline bool contains(const int id) {
				ASSERT((id < size) && (id >= 0));
				return(age[id] != -1);
			}

			/**
			 * @brief update abstract cache set state of a fully associative set,
			 * i.e., this cache has 'A' lines, and an item which belongs to this
			 * set could be in any of these lines.
			 *
			 * Each potential conflicting cache item has a unique ID (from LBlockBuilder)
			 * and here we track age of these IDs.
			 *
			 * Actually, abstract cache states are sets (one per age), but since every
			 * item can occur at most once per set [Ferdinand99, (4)], it is
			 * enough to store the age of each ID here. Consequently, all IDs with the same age
			 * then belong to the same set
			 *
			 * If memory 'id' is accessed, then all elements in the cache set
			 * do 'aging' by one, and m becomes youngest.
			 *
			 * Ferdinand calls this "abstract set update function"
			 */
			inline void inject(const int id) {
				if (contains(id)) {
					// [Ferdinand99], p.11: all items before m age by one, m becomes first
					for (int i = 0; i < size; i++) {
						if ((age[i] < age[id]) && (age[i] != -1))
							age[i]++;
					}
					age[id] = 0; ///< unnecessary. Done few lines down anyway.
				} else {
					// [Ferdinand99], p.11: all items age by one, m becomes first. The set subtraction
					// is not required, since we don't use sets in this implementation, but rather
					// track the age of each concrete memory block.
					for (int i = 0; i < size; i++) {
						if (age[i] != -1)
							age[i]++;
						if (age[i] == A)
							age[i] = -1; // this is evicted.
					}
				}
				age[id] = 0;
			}

			inline void print(elm::io::Output &output) const {
				bool first = true;
				output << "[";
				for (int i = 0; i < size; i++) {
					if (age[i] != -1) {
						if (!first) {
							output << ", ";
						}
						output << "cid=" << i << ":" << age[i];
						//output << i;
						//output << ":";
						//output << age[i];

						first = false;
					}
				}
				output << "]";

			}

			inline int getAge(int id) const {
				ASSERT(id < size);
				return(age[id]);
			}

			inline void setAge(const int id, const int _age) {
				ASSERT(id < size);
				ASSERT((_age < A) || (_age == -1));
				age[id] = _age;
			}


			/*
			 * For each cache block (cid) belonging to the set:
			 * age[block] represents its age, from 0 (newest) to A-1 (oldest).
			 * The value -1 means that the cache block is not in the set.
			 */
			int *age;
	};

	private:

	// Fields
	LBlockSet *lbset;
	WorkSpace *fw;
	const int line;
	const hard::Cache *cache;
	Domain bot;
	Domain ent;

	public:
	Domain callstate;

	// Public fields

	// Constructors
	MUSTProblem(const int _size, LBlockSet *_lbset, WorkSpace *_fw, const hard::Cache *_cache, const int _A);

	// Destructors
	~MUSTProblem();

	// Problem methods
	const Domain& bottom(void) const;
	const Domain& entry(void) const;



	inline void lub(Domain &a, const Domain &b) const {
		a.lub(b);
	}
	inline void assign(Domain &a, const Domain &b) const {
		a = b;
	}
	inline bool equals(const Domain &a, const Domain &b) const {
		return (a.equals(b));
	}


	void update(Domain& out, const Domain& in, BasicBlock* bb);
	inline void enterContext(Domain &dom, BasicBlock *header, hai_context_t ctx) {

	}

	inline void leaveContext(Domain &dom, BasicBlock *header, hai_context_t ctx) {

	}

};

elm::io::Output& operator<<(elm::io::Output& output, const MUSTProblem::Domain& dom);

}

#endif /*CACHE_MUSTPROBLEM_H_*/
