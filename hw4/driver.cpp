#include "DayofYearSet.h"
using namespace doys;

int main(){
	
	// declarations
	list<DayofYearSet::DayofYear> l1, l2;
	fstream file;

	cout << "Calling DayofYear constructors..." << endl << endl;
	DayofYearSet::DayofYear d1("January", 15);
	DayofYearSet::DayofYear d2("February", 26);
	DayofYearSet::DayofYear d3("November", 11);
	DayofYearSet::DayofYear d4("June", 6);
	DayofYearSet::DayofYear d5("August", 17);
	DayofYearSet::DayofYear d6("April", 30);

	l1 = {d1, d2, d3};
	l2 = {d2, d6, d1, d5, d3};

	cout << "Calling DayofYearSet constructors..." << endl << endl;
	DayofYearSet set1(l1);
	DayofYearSet set2(l2);

	cout << "Set 1: " << set1 << endl << "Set 2: " << set2 << endl;
	cout << "Adding elements to sets...(April 30 to set1, June 6 to set2)" << endl << endl;
	set1 = set1 + d6;
	set2 = set2 + d4;
	cout << "Set 1: " << set1 << endl << "Set 2: " << set2 << endl;
	cout << "Removing January 15 from set 1, November 11 from set 2..." << endl << endl;
	set1.remove(d1);
	set2 = set2 - d3;
	cout << "Set 1: " << set1 << endl << "Set 2: " << set2 << endl;
	cout << "Intersection set: " << (set1 ^ set2) << endl;
	cout << "Difference set(set1 - set2): " << (set1 - set2) << endl;
	DayofYearSet A = set1 + set2;
	cout << "Union set(set1 + set2): " << A << endl;
	cout << "(set1 == set2) => "  << (set1 == set2) << "	" << "(set1 != set2) => " << (set1 != set2) << endl << endl;
	cout << "Writing sets to sets.txt..." << endl;
	file.open("sets.txt", ios::out);
	file << "{ ";
	for (int i = 0; i < set1.size()-1; i++)
	file << set1[i].getMonth() << " " << set1[i].getDay() << ", ";
	file << set1[set1.size()-1].getMonth() << " " << set1[set1.size()-1].getDay() << " }" << endl;
	file << endl;
	file << "{ ";
	for (int i = 0; i < set2.size()-1; i++)
	file << set2[i].getMonth() << " " << set2[i].getDay() << ", ";
	file << set2[set2.size()-1].getMonth() << " " << set2[set2.size()-1].getDay() << " }" << endl;
	cout << "Done." << endl;
	
	return 0;
}