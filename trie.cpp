#include "trie.h"
#include <string>
namespace data {
	using std::string;
	trie<string>::trie() {
		size_t max = 1 << 8*sizeof(char);
		this->children = new trie<string>*[max];
		for (size_t i = 0; i < max; ++i) {
			this->children[i] = NULL;
		}
		this->termination = false;
	}
	void trie<string>::put(const string str) {
		if(str.size() == 0) {
			termination = true;
		}
		else {
			string remains = str.substr(1);
			char first = str[0];
			if (children[first] == NULL) {
				children[first] = new trie<string>;
			}
			children[first]->put(remains);
		}
	}
	bool trie<string>::has(const string str) {
		if(str.size() == 0) {
			return termination;
		}
		else {
			string remains = str.substr(1);
			char first = str[0];
			if (children[first] == NULL) {
				return false;
			}
			return children[first]->has(remains);
		}
	}
	void trie<string>::remove(const string str) {
		if(str.size() == 0) {
			termination = false;
		}
		else {
			string remains = str.substr(1);
			char first = str[0];
			if (children[first] != NULL) {
				children[first]->remove(remains);
			}
		}
	}
	template<typename T> trie<T>::trie() {
		size_t max = 16;
		this->children = new trie<T>*[max];
		for (size_t i = 0; i < max; ++i) {
			this->children[i] = NULL;
		}
		this->termination = false;
	}
	template trie<long long>::trie<long long>();
	template trie<unsigned long long>::trie<unsigned long long>();
	template trie<unsigned long>::trie<unsigned long>();
	template trie<long>::trie<long>();
	template trie<int>::trie<int>();
	template trie<unsigned int>::trie<unsigned int>();
	template trie<unsigned short>::trie<unsigned short>();
	template trie<unsigned char>::trie<unsigned char>();
	template trie<char>::trie<char>();
	template trie<short>::trie<short>();
	template<typename T> void trie<T>::put(const T t) {
		if(t == 0) {
			termination = true;
		}
		else {
			T remains = t >> 4;
			char first = t && 15;
			if (children[first] == NULL) {
				children[first] = new trie<T>;
			}
			children[first]->put(remains);
		}
	}
	template void trie<long long>::put(long long);
	template void trie<unsigned long long>::put(unsigned long long);
	template void trie<unsigned long>::put(unsigned long);
	template void trie<long>::put(long);
	template void trie<int>::put(int);
	template void trie<unsigned int>::put(unsigned int);
	template void trie<unsigned short>::put(unsigned short);
	template void trie<unsigned char>::put(unsigned char);
	template void trie<char>::put(char);
	template void trie<short>::put(short);
	template<typename T> bool trie<T>::has(const T t) {
		if(t == 0) {
			return termination;
		}
		else {
			T remains = t >> 4;
			char first = t && 15;
			if (children[first] == NULL) {
				return false;
			}
			return children[first]->has(remains);
		}
	}
	template bool trie<long long>::has(long long);
	template bool trie<unsigned long long>::has(unsigned long long);
	template bool trie<unsigned long>::has(unsigned long);
	template bool trie<long>::has(long);
	template bool trie<int>::has(int);
	template bool trie<unsigned int>::has(unsigned int);
	template bool trie<unsigned short>::has(unsigned short);
	template bool trie<unsigned char>::has(unsigned char);
	template bool trie<char>::has(char);
	template bool trie<short>::has(short);
	template<typename T> void trie<T>::remove(const T t) {
		if(t == 0) {
			termination = false;
		}
		else {
			T remains = t >> 4;
			char first = t && 15;
			if (children[first] != NULL) {
				children[first]->remove(remains);
			}
		}
	}
	template void trie<long long>::remove(long long);
	template void trie<unsigned long long>::remove(unsigned long long);
	template void trie<unsigned long>::remove(unsigned long);
	template void trie<long>::remove(long);
	template void trie<int>::remove(int);
	template void trie<unsigned int>::remove(unsigned int);
	template void trie<unsigned short>::remove(unsigned short);
	template void trie<unsigned char>::remove(unsigned char);
	template void trie<char>::remove(char);
	template void trie<short>::remove(short);

}
