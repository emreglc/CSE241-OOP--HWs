#include "PFArrayPlus.h"
using namespace pfa;

// no parameter constructor
template<class C>
PFArrayPlus<C>::PFArrayPlus() :cap(50), used(0){
	this->arr = shared_ptr<C>(new C[cap]);
}

// one parameter constructor which takes size as parameter
template<class C>
PFArrayPlus<C>::PFArrayPlus(int size) :cap(size), used(0){
	this->arr = shared_ptr<C>(new C[cap]);
}

// copy constructor
template<class C>
PFArrayPlus<C>::PFArrayPlus(const PFArrayPlus<C>& pfaObj){

	shared_ptr<C> temp(new C[pfaObj.cap]);
	
	this->used = pfaObj.used;
	this->cap = pfaObj.cap;

	IteratorPlus<C> pfaI;
	IteratorPlus<C> tempI;

	pfaI = pfaObj.begin();
	tempI = temp.get();

	for (int i = 0; i < this->used; i++){
		*tempI = *pfaI;
		++tempI;
		++pfaI;
	}
	
	this->arr = temp;

}

// move copy constructor 
template<class C>
PFArrayPlus<C>::PFArrayPlus(PFArrayPlus<C>&& pfaObj){
	
	this->used = pfaObj.used;
	this->cap = pfaObj.cap;
	this->arr = move(pfaObj.arr);
	pfaObj.used = 0;
	pfaObj.cap = 0;
	pfaObj.arr = nullptr;

}

// copy assignment operator
template <class C>
void PFArrayPlus<C>::operator=(const PFArrayPlus<C>& pfaObj){
	
	if (this == &pfaObj) return;

	this->capacity = pfaObj.capacity;
	this->used = pfaObj.used;

	shared_ptr<C> temp(new C[cap]);
	IteratorPlus<C> pfaI;
	IteratorPlus<C> tempI;

	pfaI = pfaObj.begin();
	tempI = temp.get();

	for (int i = 0; i < this->used; i++){
		*tempI = *pfaI;
		++tempI;
		++pfaI;
	}

	this->arr = temp;

}

// move assignment operator
template <class C>
void PFArrayPlus<C>::operator=(PFArrayPlus<C>&& pfaObj){
	
	this->arr = move(pfaObj.arr);
	this->cap = pfaObj.cap;
	this->used = pfaObj.used;
	pfaObj.used = 0;
	pfaObj.cap = 0;
	pfaObj.arr = nullptr;

}

// push_back function to add items to the array
template<class C>
void PFArrayPlus<C>::push_back(const C& element){

	if(this->used == this->cap - 1)
	{
		PFArrayPlus<C> temp(++cap);
		copy(this->begin(), this->end(), temp.begin());
		this->arr = move(temp.arr);
	}
	*(arr.get() + used++) = element;

}

// overloaded index operator
template<class C>
C& PFArrayPlus<C>::operator[](int index){

	try{
		if((index >= used) || index < 0){
			throw index;
		}else{
			return *(arr.get() + index);
		}
	}
	catch(int index){
		cerr << "ERR-->Invalid index in PFArray..";
		return *arr.get();
	}

}

// overloaded const index operator for const objects
template<class C>
const C& PFArrayPlus<C>::operator[](int index) const{

	try{
		if((index >= used) || index < 0){
			throw index;
		}else{
			return *(arr.get() + index);
		}
	}
	catch(int index){
		cerr << "ERR-->Invalid index in PFArray..";
		return *arr.get();
	}

}

// erase function removes the element at the specified position using the given iterator
template<class C>
void PFArrayPlus<C>::erase(const IteratorPlus<C>& it){

	PFArrayPlus<C> temp(this->cap);

	try
	{
		if(it.getData() > this->end().getData() || it.getData() < this->begin().getData()) throw it.getData();
		else{
			for (int i = 0; i < this->used; i++)
				if ((*this)[i] != *it)
					temp.push_back((*this)[i]);
		*this = move(temp);
		}				
	}
	catch(const C* data)
	{
		cerr << "ERROR--> Iterator is out of range, terminating the program....\n";
		exit(0);
	}
	
}