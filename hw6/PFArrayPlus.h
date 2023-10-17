#ifndef PFARRAYPLUS_H
#define PFARRAYPLUS_H

#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

#include "IteratorPlus.h"
using namespace pfa;

namespace pfa{

	template<class C>
	class PFArrayPlus{

		public:
			// constructors
			PFArrayPlus();
			PFArrayPlus(int cap);
			PFArrayPlus(const PFArrayPlus<C>& obj);
			PFArrayPlus(PFArrayPlus<C>&& obj);

			// overloaded operators
			C& operator[](int index);
			const C& operator[](int index) const;
			void operator=(const PFArrayPlus<C>& obj);
			void operator=(PFArrayPlus<C>&& obj);

			// other member functions
			void push_back(const C& element);
			inline bool full() const{return cap == used;};
			inline const int getCapacity() const{return cap;};
			inline const int size() const{return used;};
			inline void emptyArray(){used = 0;};

			// begin and end functions return iterators either at the begin or the end
			inline const IteratorPlus<C> cbegin() const{return IteratorPlus<C>(arr.get());};
			inline const IteratorPlus<C> cend() const{return IteratorPlus<C>(arr.get() + used);};
			inline IteratorPlus<C> begin() const{return IteratorPlus<C>(arr.get());};
			inline IteratorPlus<C> end() const{return IteratorPlus<C>(arr.get() + used);};

			void erase(const IteratorPlus<C>& it);
			inline void clear(){used = 0;};
			inline bool empty() const{return used == 0;};
			inline void print() const {for_each(this->begin(), this->end(), [](const C &var){ cout << var << " "; }); cout << endl;};
		private:
			// shared pointer which is the main array data
			shared_ptr<C> arr;
			int cap;// capacity of the array
			int used;// used capacity of the array

	};

}

#endif