#include "linkedlist.h" 
#include "trie.h"
#include "splay.h"
#include "bogo.h"
#include "avl.h"
#include "util.h"
#include "beap.h"
#include "array.h"
#include <cstddef>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using data::linkedlist;
using data::trie;
using data::splayset;
using data::splaymap;
using data::bogoweb;
using data::avlset;
using data::avlmap;
using data::beap;
using data::mergesort;
using data::heapsort;
using data::priorityq;
using data::randomData;
using data::array;

template<typename T> void test(string description, T value, T expected) {
	cout << description << ":\t" << (value == expected ? "Pass" : "Fail") << endl;
}
template <> void test(string description, string value, string expected) {
	cout << description << ":\t" << (value.compare(expected) == 0 ? "Pass" : "Fail") << endl;
}
template <typename P> void testArray(string description, P ptr, P other, size_t size, int step = 1) {
	cout << description << ":\t";
	for (size_t i = 0; i < size; ++i) {
		int index = i * step;
		if (ptr[i] !=  other[index]) {
			cout << "Fail" << endl;
			return; // May be better with goto, but this is a testing program that should be easy to follow
		}
	}
	cout << "Pass" << endl;
}

void section(string title) {
	cout << "\n\n== " << title << " ==\n";
}

int main() {
	section("Linked List");
	int six = 6;
	linkedlist<linkedlist<int> > temp;
	linkedlist<int> sicks(six);
	test("Single element list creation",sicks.at(0),6);
	size_t size = 26;
	char* alphabet = new char[size];
	char* alphatest = new char[size];
	linkedlist<char> alpha2;
	for(size_t letter = 0; letter < size; letter++)
	{
		alphabet[letter] = 'a' + letter;
		alpha2.push_back(alphabet[letter]);
	}
	linkedlist<char> alpha(alphabet,size);
	for(size_t index = 0; index < size; index++)
	{
		alphatest[index] = alpha.at(index);
	}
	testArray("Linked list created from array",alphabet,alphatest,size);
	for(linkedlist<char>::iterator i = alpha.begin(); i != alpha.end(); i++) {
		static size_t index = 0;
		alphatest[index++] = *i;
	}
	testArray("Linked list iterator successfully iterates over the elements", alphabet, alphatest, size);
	for(size_t index = 0; index < size; index++)
	{
		alphatest[index] = alpha2.at(index);
	}
	testArray("Linked list at function works as intended", alphabet, alphatest, size);
	linkedlist<char> alpha3;
	for(size_t letter = 1; letter <= size; letter++)
	{
		alpha3.push_front(alphabet[size - letter]);
	}
	for(size_t index = 0; index < size; index++)
	{
		alphatest[index] = alpha3.at(index);
	}
	testArray("Linked list push_front works as intended", alphabet, alphatest, size);
	while(alpha3.size()) {
		static size_t index = 0;
		alphatest[index++] = alpha3.pop_front();
	}
	test("Popping all elements makes list empty", alpha3.empty(), true);
	testArray("Linked list pops elements from front correctly", alphabet, alphatest, size);
	while(alpha2.size()) {
		static size_t i = size;
		alphatest[--i] = alpha2.pop_back();
	}
	testArray("Linked list pops elements from back correctly", alphabet, alphatest, size);
	for (linkedlist<char>::iterator it = alpha.rbegin(); it != alpha.rend(); ++it) {
		static size_t i = size;
		alphatest[--i] = *it;
	}
	testArray("Linked list reverse iterator works correctly", alphabet, alphatest, size);
	alpha.reverse();
	for (linkedlist<char>::iterator it = alpha.begin(); it != alpha.end(); ++it) {
		static size_t i = size;
		alphatest[--i] = *it;
	}
	testArray("Linked list reverses correctly", alphabet, alphatest, size);
	alpha.clear();
	test("Clearing linked list makes size 0", alpha.size(), (size_t) 0);
	section("Trie");
	trie<string> dict;
	test("String trie returns true in new value put",dict.put("hello world"),true);
	test("String trie has what we put",dict.has("hello world"),true);
	test("trie<string> now has 1 element",dict.size(),(size_t) 1);
	test("String trie remove indicates it has changed the trie",dict.remove("hello world"),true);
	test("trie<string> no longer has what we remove", dict.has("hello world"),false);
	test("trie<string> now has no elements",dict.size(),(size_t) 0);
	trie<long long> phbook;
	test("trie<long long> put indicates the trie has changed",phbook.put(1234567),true);
	test("trie<long long> has what we put", phbook.has(1234567), true); 
	test("trie<long long> now has one element", phbook.size(), (size_t) 1);
	test("trie<long long> remove indicates the trie has changed",phbook.remove(1234567),true);
	test("trie<long long> no longer has what we remove", phbook.has(1234567), false);
	test("trie<long long> now has no elements", phbook.size(), (size_t) 0);
	trie<char> lett;
	lett.put('a');
	test("trie<char> has what we put", lett.has('a'), true);
	lett.remove('a');
	test("trie<char> no longer has what we remove", lett.has('a'), false);
	cout << "hasAll:\t";
	char* theLetters = new char[5];
	theLetters[0] = 'a';
	theLetters[1] = 'b';
	theLetters[2] = 'c';
	lett.put('a');
	test("trie<char> hasAll of an empty array", lett.hasAll(theLetters,0), true);
	lett.put('b');
	test("trie<char> does not hasAll things it doesn't have", lett.hasAll(theLetters,3), false);
	test("trie<char> hasAll things it does have", lett.hasAll(theLetters,2), true);
	test("trie<char> counts its elements correctly", lett.size(), (size_t) 2);
	section("Splay Set");
	splayset<unsigned int> digits;
	test("Constructed with size zero", digits.size(), (size_t) 0);
	for (unsigned int i = 0; i < 10; ++i) {
		digits.add(i);
	}
	bool sstest = true;
	for (unsigned int i = 0; i < 10; ++i) {
		if (!digits.contains(i)) {
			sstest = false;
		}
	}
	test("Added ten values and contains those values", sstest, true);
	test("Now has 10 values",digits.size(), (size_t) 10);
	sstest = true;
	for (unsigned int i = 9; i < 10; --i) {
		digits.remove(i);
		if (digits.contains(i)) {
			sstest = false;
		}
	}
	test("Does not contain values after removing them", sstest, true);
	section("Splay Map");
	splaymap<unsigned char,unsigned int> charstodigits;
	test("Constructed with size zero", charstodigits.size(),(size_t)0);
	for (unsigned int i = 0; i < 10; ++i) {
		charstodigits.put((char)48 + i,i);
	}
	bool smtest = true;
	for (char i = '0'; i <= '9'; ++i) {
		if (charstodigits.get(i) != i - 48) {
			smtest = false;
		}
	}
	test("Added ten values and contains them",smtest,true);
	test("Now has ten values",charstodigits.size(),(size_t)10);
	smtest = true;
	for (char i = '0'; i <= '9'; ++i) {
		charstodigits.remove(i);
		if (charstodigits.get(i) != NULL) {
			smtest = false;
			cout << i << ' ';
		}
	}
	test("Does not contain removed values",smtest,true);
	section("Bogoweb");
	bogoweb<unsigned int> twoDigitNumbers;
	for (unsigned int i = 0; i < 100; ++i) {
		twoDigitNumbers.insert(i);
	}
	bool bwctest = true;
	for (unsigned int i = 0; i < 100; ++i) {
		if (!twoDigitNumbers.contains(i)) {
			bwctest = false;
		}
	}
	test("Contains all of those elements",bwctest,true);
	bwctest = true;
	for (unsigned int i = 100; i < 200; ++i) {
		if (twoDigitNumbers.contains(i)) {
			bwctest = false;
		}
	}
	test("Does not contain other elements",bwctest,true);
	section("AVL Set");
	avlset<char> hexChars;
	for (char letter = 'A'; letter <= 'F'; ++letter) {
		hexChars.add(letter);
	}
	bool avlstest = true;
	for (char letter = 'A'; letter <= 'F'; ++letter) {
		if(!hexChars.contains(letter)) {
			avlstest = false;
		}
	}
	test("Adds 6 values and contains them",avlstest,true);
	avlstest= true;
	for (char letter = 'A'; letter <= 'F'; ++letter) {
		hexChars.remove(letter);
		if (hexChars.contains(letter)) {
			avlstest = false;
		}
	}
	test("Removes them and no longer contains them",avlstest,true);
	section("AVL Map");
	avlmap<char,unsigned int> offsetMap;
	for (char i = 0; i < 16; ++i) {
		offsetMap.put(i,(unsigned int)i + 48);
	}
	bool avlmtest = true;
	for (char i = 0; i < 16; ++i) {
		if (offsetMap.get(i) != (unsigned int) i + 48) {
			avlmtest = false;
		}
	}
	cout << "Contains all 16 values inserted:\t";
	if (avlmtest) {
		cout << "Pass";
	}
	else {
		cout << "Fail";
	}
	section("Beap");
	bool btest = true;
	beap<size_t> bigNums;
	for (size_t i = 100; i > 88; --i) {
		bigNums.insert(i);
	}
	test("Insert 12 values out of order and then count 12",bigNums.size(),(size_t)12);
	for (size_t i = 89; i < 101; ++i) {
		if (bigNums.pop() != i) {
			btest = false;
		}
	}
	test("They pop in order",btest,true);
	section("Priority Queue");
	priorityq<size_t,char> ruins;
	for (char i = 'A'; i <= 'Z'; ++i) {
		ruins.insert(randomData<size_t>(),i);
	}
	test("Insert 26 values in random order and count 26",ruins.size(),(size_t)26);
	section("Array");
	array<int> list(1);
	test("Array constructed with no values",list.count(),(size_t) 0);
	list.push_back(1);
	test("Array has value after push_back",list[0],1);
	list.push_front(2);
	test("Array has value after push_front",list[0],2);
	test("Array retains value after push_front",list[1],1);
	test("Array now contains 2 values",list.count(),(size_t) 2);
	list.push_front(3);
	list.push_back(4);
	list.push_front(5);
	list.push_front(8);
	test("Pushes 4 more elements and has them", list[0] + list[1] + list[2] + list[3] + list[4] + list[5], 23);
	section("Util");
	int* array = new int[10];
	for (size_t i = 0; i < 10; ++i) {
		array[i] = 9 - i;
	}
	cout << "Mergesort:\t";
	mergesort(array,10);
	bool test = true;
	for (size_t i = 0; i < 10; ++i) {
		if (array[i] != i) {
			cout << i;
			test = false;
		}
	}
	if (test) {
		cout << "Pass";
	}
	else {
		cout << "Fail";
	}
	cout << "\nHeapsort:\t";
	for (size_t i = 0; i < 10; ++i) {
		array[i] = 9 - i;
	}
	heapsort(array,10);
	test = true;
	for (size_t i = 0; i < 10; ++i) {
		if (array[i] != i) {
			cout << i;
			test = false;
		}
	}
	if (test) {
		cout << "Pass";
	}
	else {
		cout << "Fail";
	}
	cout << "\nRandomness:";
	cout << "\n\tRandom ints:";
	for (size_t i = 0; i < 5; ++i) {
		cout << "\t" << randomData<int>();
	}
	cout << "\n\tRandom bools:";
	for (size_t i = 0; i < 10; ++i) {
		cout << "\t" << randomData<bool>();
	}	cout << '\n' << endl;
	return 0;
}
