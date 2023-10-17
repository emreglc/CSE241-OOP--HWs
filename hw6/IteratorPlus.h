#ifndef ITERATORPLUS_H
#define ITERATORPLUS_H

// ------- NO CPP FILE BECAUSE ALL FUNCTIONS ARE INLINE --------

namespace pfa{

	template<class C>
	class IteratorPlus{

		public:
			using value_type = C;
            using pointer = C *;
            using reference = C &;
            using difference_type = ptrdiff_t;
			using iterator_category = random_access_iterator_tag;
			
			IteratorPlus() : data(nullptr){};// default constructor
			IteratorPlus(C* it) : data(it){};// copy constructor
			IteratorPlus(const IteratorPlus& it) : data(it.data){};// copy constructor v2
			inline const C* getData() const{return data;};// getter for the data of the iterator

			// overloaded operators section
			inline bool operator==(const IteratorPlus& it){return data == it.data;};
			inline bool operator!=(const IteratorPlus& it){return data != it.data;};
			inline IteratorPlus& operator=(C* it){this->data = it; return *this;};
			inline IteratorPlus& operator=(const IteratorPlus& it){this->data = it.data; return *this;};
			inline C& operator*() const{return *data;};
			inline C* operator->() const{return data;};
			inline friend IteratorPlus operator+(const IteratorPlus& it, int i){return IteratorPlus(it.data + i);};
			inline friend IteratorPlus operator+(int i, const IteratorPlus& it){return IteratorPlus(it.data + i);};
			inline int operator-(const IteratorPlus& it){return data - it.data;};
			inline friend IteratorPlus operator-(const IteratorPlus& it, int i){return IteratorPlus(it.data - i);};
			inline IteratorPlus& operator++(){++data; return *this;};
			inline IteratorPlus operator++(int){IteratorPlus temp = *this; ++data; return temp;};
			inline friend IteratorPlus operator+=(IteratorPlus& it, int i){return IteratorPlus(it.data + i);};
			inline friend IteratorPlus operator+=(int i, IteratorPlus& it){return IteratorPlus(it.data + i);};
			inline friend IteratorPlus operator-=(IteratorPlus& it, int i){return IteratorPlus(it.data - i);};
			inline IteratorPlus& operator--(){--data; return *this;};
			inline IteratorPlus operator--(int){IteratorPlus temp = *this; --data; return temp;};
			inline friend bool operator<(const IteratorPlus &itL, const IteratorPlus &itR){ return (*itL) < (*itR);};
            inline bool operator<(const IteratorPlus &it) const{return (this->data) < (it.data);};
			inline friend bool operator>(const IteratorPlus &itL, const IteratorPlus &itR){ return (*itL) > (*itR);};
            inline bool operator>(const IteratorPlus &it) const{return (this->data) > (it.data);};
			// overloaded operators end

		private:
			// data of the iterator which is a pointer of any class
			C * data;

	};

}

#endif