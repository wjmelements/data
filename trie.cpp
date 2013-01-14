#include "trie.h"
#include <string>
namespace data {
	using std::string;
	template <> trie<string>::trie() {
		size_t max = 1 << 8*sizeof(char);
		this->children = new trie<string>*[max];
		for (size_t i = 0; i < max; ++i) {
			this->children[i] = NULL;
		}
		this->termination = false;
	}
	template <> void trie<string>::put(const string str) {
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
	template <> bool trie<string>::has(const string str) {
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
	template <> void trie<string>::remove(const string str) {
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
	template trie<long long>::trie();
	template trie<unsigned long long>::trie();
	template trie<unsigned long>::trie();
	template trie<long>::trie();
	template trie<int>::trie();
	template trie<unsigned int>::trie();
	template trie<unsigned short>::trie();
	template trie<unsigned char>::trie();
	template trie<char>::trie();
	template trie<short>::trie();

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

	template<typename T> trie<T>::iterator::iterator() {
		forwards = true;
		root = NULL;
		current = 0;
	}
	template trie<long long>::iterator::iterator();
	template trie<unsigned long long>::iterator::iterator();
	template trie<unsigned long>::iterator::iterator();
	template trie<long>::iterator::iterator();
	template trie<int>::iterator::iterator();
	template trie<unsigned int>::iterator::iterator();
	template trie<unsigned short>::iterator::iterator();
	template trie<unsigned char>::iterator::iterator();
	template trie<char>::iterator::iterator();
	template trie<short>::iterator::iterator();

	template<typename T> trie<T>::iterator::iterator(bool forwards, trie<T>* root, T current) {
		this->forwards = forwards;
		this->root = root;
		this->current = current;
	}
	template trie<long long>::iterator::iterator(bool forwards, trie<long long>* root, long long current);
	template trie<unsigned long long>::iterator::iterator(bool forwards, trie<unsigned long long>* root, unsigned long long current);
	template trie<unsigned long>::iterator::iterator(bool forwards, trie<unsigned long>* root, unsigned long current);
	template trie<long>::iterator::iterator(bool forwards, trie<long>* root, long current);
	template trie<int>::iterator::iterator(bool forwards, trie<int>* root, int current);
	template trie<unsigned int>::iterator::iterator(bool forwards, trie<unsigned int>* root, unsigned int current);
	template trie<unsigned short>::iterator::iterator(bool forwards, trie<unsigned short>* root, unsigned short current);
	template trie<unsigned char>::iterator::iterator(bool forwards, trie<unsigned char>* root, unsigned char current);
	template trie<char>::iterator::iterator(bool forwards, trie<char>* root, char current);
	template trie<short>::iterator::iterator(bool forwards, trie<short>* root, short current);

	template<typename T> trie<T>::iterator::iterator(const iterator &original) {
		forwards = original.forwards;
		root = original.root;
		current = original.current;
	}
	template trie<long long>::iterator::iterator(const iterator &original);
	template trie<unsigned long long>::iterator::iterator(const iterator &original);
	template trie<unsigned long>::iterator::iterator(const iterator &original);
	template trie<long>::iterator::iterator(const iterator &original);
	template trie<int>::iterator::iterator(const iterator &original);
	template trie<unsigned int>::iterator::iterator(const iterator &original);
	template trie<unsigned short>::iterator::iterator(const iterator &original);
	template trie<unsigned char>::iterator::iterator(const iterator &original);
	template trie<char>::iterator::iterator(const iterator &original);
	template trie<short>::iterator::iterator(const iterator &original);

	template <typename T> typename trie<T>::iterator& trie<T>::iterator::operator= (const iterator &original) {
		forwards = original.forwards;
		root = original.root;
		current = original.current;
		return *this;
	}
	template typename trie<long long>::iterator& trie<long long>::iterator::operator=(const iterator &original);
	template typename trie<unsigned long long>::iterator& trie<unsigned long long>::iterator::operator=(const iterator &original);
	template typename trie<unsigned long>::iterator& trie<unsigned long>::iterator::operator=(const iterator &original);
	template typename trie<long>::iterator& trie<long>::iterator::operator=(const iterator &original);
	template typename trie<int>::iterator& trie<int>::iterator::operator=(const iterator &original);
	template typename trie<unsigned int>::iterator& trie<unsigned int>::iterator::operator=(const iterator &original);
	template typename trie<unsigned short>::iterator& trie<unsigned short>::iterator::operator=(const iterator &original);
	template typename trie<unsigned char>::iterator& trie<unsigned char>::iterator::operator=(const iterator &original);
	template typename trie<char>::iterator& trie<char>::iterator::operator=(const iterator &original);
	template typename trie<short>::iterator& trie<short>::iterator::operator=(const iterator &original);

}
