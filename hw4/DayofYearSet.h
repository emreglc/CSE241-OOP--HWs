#ifndef DAYOFYEARSET_H
#define DAYOFYEARSET_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>
using namespace std;

namespace doys{// main namespace declaration

	class DayofYearSet{// the outer class which is a set of dayofyear objects

		public:
			class DayofYear{// dayofyear class which holds a specific date data

				public:
					DayofYear(const string& month, const int day);
					DayofYear();
					const string& getMonth() const{return this->month;};
					int getDay() const{return this->day;};
					void setMonth(const string& month){this->month = month;};
					void setDay(int day){this->day = day;};
					friend std::ostream& operator<<(std::ostream& os, DayofYearSet& doys);
					bool operator==(DayofYear& d) const;
				private:
					string month;
					int day;

			};
			DayofYearSet(list<DayofYear> l);
			DayofYearSet(const int size);
			~DayofYearSet();
			void remove(const DayofYear& doy);
			const int size() const;
			DayofYearSet& operator+(DayofYear& doy);
			DayofYearSet operator+(DayofYearSet& doys);
			DayofYearSet& operator-(DayofYear& doy);
			DayofYearSet& operator-(DayofYearSet& doys);
			DayofYearSet& operator^(DayofYearSet& doys);
			bool operator==(DayofYearSet& doys);
			bool operator!=(DayofYearSet& doys);
			DayofYearSet& operator!();
			DayofYear& operator[](const int i);

		private:
			DayofYear * set;// the pointer that holds dayofyear objects 
			int _size;

	};

	std::ostream& operator<<(std::ostream& os, DayofYearSet& doys);

}	

#endif