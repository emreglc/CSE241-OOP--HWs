#include "DayofYearSet.h"
using namespace doys;

// constructor which takes a list as parameter and
// initializes the member array with list elements
DayofYearSet::DayofYearSet(list<DayofYear> l){

	this->_size = l.size();

	this->set = new DayofYear[_size];

	for (auto i = 0; i < this->_size; i++)
	{
		this->set[i] = l.front();
		l.pop_front();
	}
	

}

// another simple constructor without initialization
DayofYearSet::DayofYearSet(const int size){
	this->_size = size;
	this->set = new DayofYear[_size];
}

// destructor
DayofYearSet::~DayofYearSet(){
	delete[] this->set;
	this->set = nullptr;
}

// remove function removes an element inside dayofyearset if it exists
void DayofYearSet::remove(const DayofYear& doy){

	DayofYear * temp;

	for (int i = 0; i < this->_size; i++)
	{
		if(doy == this->set[i]){

			temp = new DayofYear[--(this->_size)];
			for (int j = 0, k = 0; j < this->_size + 1; j++, k++)
			{
				if(j != i) temp[k] = this->set[j];
				else k--;
			}

			delete[] this->set;
			this->set = nullptr;
			this->set = new DayofYear[_size];
			for (int t = 0; t < this->_size; t++)
				this->set[t] = temp[t];
			delete[] temp;
			temp = nullptr;
			
		}
	}

}

// size function returns the size of the set
const int DayofYearSet::size() const{
	return this->_size;
}

// overloaded index operator to access members of the set easily
DayofYearSet::DayofYear& DayofYearSet::operator[](const int i){
	return this->set[i];
}

// overloaded ostream operator to print sets on terminal
std::ostream& doys::operator<<(std::ostream& os, DayofYearSet& doys){

	os << "{ ";
	for (auto i = 0; i < doys.size()-1; i++)
		os << doys[i].getMonth() << " " << doys[i].getDay() << ", ";
	os << doys[doys.size()-1].getMonth() << " " << doys[doys.size()-1].getDay() << " }" << endl;
	return os;

}

// overloaded addition operator to add an element to the set
DayofYearSet& DayofYearSet::operator+(DayofYear& doy){

	auto flag = 0;

	for (auto i = 0; i < this->_size; i++)
		if (doy == this->set[i])
			flag = 1;

	if (flag == 1) return *this;

	int tempsize = _size;
	DayofYear * temp = new DayofYear[tempsize];
	for (int i = 0; i < tempsize; i++)
		temp[i] = this->set[i];
	delete[] this->set;
	this->set = nullptr;
	_size++;
	this->set = new DayofYear[_size];
	for (int i = 0; i < tempsize; i++)
		this->set[i] = temp[i];
	delete[] temp;
	temp = nullptr;
	this->set[tempsize] = doy;
	return *this;

}

// overloaded addition operator to return the union set of two sets
DayofYearSet DayofYearSet::operator+(DayofYearSet& doys){

	DayofYearSet temp(1);  
	int flag;
	temp._size = size() + doys.size();
	set = new DayofYear[temp.size()];

	for (int i = 0; i <_size; i++)
		temp.set[i] = set[i];
	int tempSize = temp.size();
	for (int i = 0; i < doys.size(); i++)
	{
		flag = 0;

		for (int j = 0; j < temp.size(); j++)
			if (doys[i] == temp[j])
				flag = 1;
		
		if (flag == 0){
			temp.set[tempSize] = doys.set[i];
			tempSize++;
		}

	}

	return temp;

}

// overloaded minus operator to remove an element from the set
DayofYearSet& DayofYearSet::operator-(DayofYear& doy){

	DayofYear * temp;

	for (int i = 0; i < this->_size; i++)
	{
		if(doy == this->set[i]){

			temp = new DayofYear[--(this->_size)];
			for (int j = 0, k = 0; j < this->_size + 1; j++, k++)
			{
				if(j != i) temp[k] = this->set[j];
				else k--;
			}

			delete[] this->set;
			this->set = nullptr;
			this->set = new DayofYear[_size];
			for (int t = 0; t < this->_size; t++)
				this->set[t] = temp[t];
			delete[] temp;
			temp = nullptr;
			
		}
	}

	return *this;

}

// overloaded minus operator to return the difference set of two sets
DayofYearSet& DayofYearSet::operator-(DayofYearSet& doys){

	DayofYear * temp = new DayofYear[this->_size];
	int tempSize = 0, flag;

	for(int i = 0; i < this->_size; i++){
		flag = 0;
		for (int j = 0; j < doys.size(); j++)
			if (this->set[i] == doys[j])
				flag = 1;

		if (flag == 0){
			temp[tempSize] = this->set[i];
			tempSize++;
		}	
	}

	/*delete[] this->set;
	this->set = nullptr;
	this->set = new DayofYear[tempSize];
	for (int i = 0; i < tempSize; i++)
		this->set[i] = temp[i];
	delete[] temp;
	temp = nullptr;
	
	return *this;*/

	DayofYearSet * tempSet = new DayofYearSet(tempSize);
	for (int i = 0; i < tempSize; i++)
		tempSet->set[i] = temp[i];
	delete[] temp;
	temp = nullptr;

	return *tempSet;

}

// overloaded ^ operator to return the intersection set of two sets
DayofYearSet& DayofYearSet::operator^(DayofYearSet& doys){

	DayofYear * temp = new DayofYear[this->_size];
	int tempSize = 0, flag;

	for (auto i = 0; i < this->_size; i++)
	{
		for (auto j = 0; j < doys.size(); j++)
		{
			if (this->set[i] == doys[j])
			{
				temp[tempSize] = this->set[i];
				tempSize++;
			}
			
		}
		
	}

	DayofYearSet * tempSet = new DayofYearSet(tempSize);
	for (auto i = 0; i < tempSize; i++)
		tempSet->set[i] = temp[i];
	delete[] temp;
	temp = nullptr;

	return *tempSet;

}

// overloaded == operator to check if two sets are equal
// regardless of the order
bool DayofYearSet::operator==(DayofYearSet& doys){

	int counter = 0, flag = 0;

	if(this->_size != doys.size()) return false;

	for (int i = 0; i < this->_size; i++)
	{
		for (int j = 0; j < this->_size; j++)
		{
			if (this->set[i] == doys.set[j])
			{
				counter++;
			}
			
		}
		
	}

	if(counter != this->_size) return false;
	else return true;

}

// overloaded != operator which does the opposite of the == operator
bool DayofYearSet::operator!=(DayofYearSet& doys){

	if(*this == doys) return false;
	else return true;

}

// dayofyear constructor which takes month(string) and day(int)
// as parameters and initializes private members
DayofYearSet::DayofYear::DayofYear(const string& month, const int day){

	if (month == "January" && day <= 31 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "February" && day <= 29 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "March" && day <= 30 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "April" && day <= 31 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "May" && day <= 30 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "June" && day <= 31 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "July" && day <= 30 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "August" && day <= 31 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "September" && day <= 30 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "October" && day <= 31 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "November" && day <= 30 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}
	if (month == "December" && day <= 31 && day >= 1)
	{
		this->month = month;
		this->day = day;
	}

}

// default dayofyear constructor
DayofYearSet::DayofYear::DayofYear(){}

// overloaded == operator for dayofyear class in order to check
// if two dates are equal without checking their data members individually
bool DayofYearSet::DayofYear::operator==(DayofYear& d) const{
	if (d.getDay() == this->getDay() && d.getMonth() == this->getMonth())
		return true;
	else 
		return false;	
}
