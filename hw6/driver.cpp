#include "PFArrayPlus.h"
#include "PFArrayPlus.cpp"
using namespace pfa;

int main(){
	
	cout << "----------Starting the tests-----------" << endl << endl << endl;

    PFArrayPlus<int> arr; 
    arr.push_back(3);
	arr.push_back(25);
	arr.push_back(7);
	arr.push_back(60);
	arr.push_back(11);
	arr.push_back(2);
	arr.push_back(6);
	arr.push_back(39);
	arr.push_back(41);
	arr.push_back(17);
    arr.print();
    cout << "Testing the index operator... 3rd element is = " << arr[2] << endl;
	cout << "Testing the index operator with and invalid index...\n(instead returns the first element)... 11st element is = " << arr[10] << endl;
    IteratorPlus<int> beg, end;
    beg = arr.cbegin();
    end = arr.cend();
    sort(beg, end);
	cout << "Testing the sort function on the array...\n";
    arr.print();
    cout<<"Testing the find function...\n";
    end = find(beg,end,11);
    cout << "11 is found at index " << end-beg << endl;
    cout << "Testing the operator * ... " << "value of index 4 -> " << *end << endl;
    end = arr.cend();
	cout << "Testing the size function... size -> " << arr.size() << endl;
	cout << "Testing the empty function... value(1: empty, 0: not empty) -> " << arr.empty() << endl;
    cout << "Printing the array using a range based for loop..." << endl;
    for(int a : arr) cout << a << " ";
    cout << endl << "Testing the erase function... Deleting the first element..." << endl;
    arr.erase(beg);
    cout<<"New array: " << endl;
    arr.print();
	cout << "Testing copy constructor..." << endl;
	cout << "Copying the array into a new array..." << endl;
	PFArrayPlus<int> empty(arr);
    cout << "Printing the first array: " << endl;
    arr.print();
    cout << "Printing the second array: " << endl;
    empty.print();
    PFArrayPlus<int> empty2 = empty;
	cout << "Testing the copy assignment operator..." << endl;
    cout << "Printing the third array..." << endl;
    empty2.print();
	cout << endl;
	cout << "Creating a char array named str1..." << endl;
    PFArrayPlus<char> str1;
	str1.push_back('h');
	str1.push_back('e');
	str1.push_back('l');
	str1.push_back('l');
	str1.push_back('o');
	cout << "Testing move assignment operator...\n" << "Move copying str1 into another array named str2..." << endl;
    PFArrayPlus<char> str2 = move(str1);
	cout << "Printing str2..." << endl;
    str2.print();
    cout << "Printing str1..." << endl;
    str1.print();
    cout << "Trying the move constructor..."<< endl << "Move copying str2 into str3..." << endl;
    PFArrayPlus<char> str3(move(str2));
    cout << "str2: ";
	str2.print();
	cout << endl << "str3: ";
	str3.print();
	cout << "End of the tests.... Last exception test to end the program...." << endl;
	cout << endl << "Trying erase function with an invalid index to test exception handling..." << endl;
	str3.erase(str3.begin()-2);

    return 0;
}