#include "linkedlist.h" 
#include <cstddef>
#include <iostream>
using namespace std;
using data::linkedlist;
int main() {
	cout << "== Linked List ==\n";
	int six = 6;
	linkedlist<linkedlist<int> > temp;
	linkedlist<int> sicks(six);
	if(sicks.at(0) != 6) {
		cout << "Single element list creation: Fail" << endl;
	}
	int size = 26;
	char* alphabet = new char[size];
	linkedlist<char> alpha2;
	for(size_t letter = 0; letter < size; letter++)
	{
		alphabet[letter] = 'a' + letter;
		alpha2.push_back(alphabet[letter]);
		cout << alphabet[letter];
	}
	cout << "\nThe following should be the above.";
	linkedlist<char> alpha(alphabet,size);
	cout << "\n";
	for(size_t index = 0; index < size; index++)
	{
		cout << alpha.at(index);
	}
	cout << "\n";
	for(linkedlist<char>::iterator i = alpha.begin(); i != alpha.end(); i++) {
		cout << *i;
	}
	cout << "\n";
	for(size_t index = 0; index < size; index++)
	{
		cout << alpha2.at(index);
	}
	cout << "\n";
	linkedlist<char> alpha3;
	for(size_t letter = 1; letter <= size; letter++)
	{
		alpha3.push_front(alphabet[size - letter]);
	}
	for(size_t index = 0; index < size; index++)
	{
		cout << alpha3.at(index);
	}
	cout << '\n';
	while(alpha3.size()) {
		cout << alpha3.pop_front();
	}
	if(!alpha3.empty()) {
		cout << "\nPopping all elements doesn't make list empty: Fail";
	}
	cout << "\nThe following should be the above backwards:\n";
	while(alpha2.size()) {
		cout << alpha2.pop_back();
	}
	cout << endl;
	for (linkedlist<char>::iterator it = alpha.rbegin(); it != alpha.rend(); it++) {
		cout << *it;
	}
	cout << endl;
	alpha.clear();
	return 0;
}
