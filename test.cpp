#include "linkedlist.h" 
#include <cstddef>
#include <iostream>
using namespace std;
int main() {
	int six = 6;
	linkedlist<linkedlist<int> > temp;
	linkedlist<int> sicks(six);
	cout << sicks.at(0) << '\n';
	int size = 26;
	char* alphabet = new char[size];
	linkedlist<char> alpha2;
	for(size_t letter = 0; letter < size; letter++)
	{
		alphabet[letter] = 'a' + letter;
		alpha2.push_back(alphabet[letter]);
		cout << "Adding: " << alphabet[letter] << endl;
		for (size_t i = 0; i < letter; i++)
		{
			cout << alpha2.at(i);
		}
		cout << endl;
	}
	linkedlist<char> alpha(alphabet,size);
	cout << '\n';
	for(size_t index = 0; index < size; index++)
	{
		cout << alpha.at(index);
	}
	cout << '\n';
	for(size_t index = 0; index < size; index++)
	{
		cout << alpha2.at(index);
	}
	cout << '\n';
}
