#ifndef trie_w
#define trie_w

#include <cstddef>
#include <string>
#include "array.h"

#ifdef PARA
#include <pthread.h>
#endif

namespace data {
	/*
		supported types:
		string
		unsigned long long
		unsigned long
		unsigned int
		unsigned short
		unsigned char
	*/
	template <typename T>
	class trie {
	private:
		trie<T>** children;
		bool termination;
		size_t count; // self and children
		#ifdef PARA
		static void* pthreadHas(void*);
		struct pthreadParam {
			trie<T>* root;
			T* elem;
		};
		#endif

	public:
		trie(); // O(sizeof(T))
		~trie();
		bool put(const T); // O(sizeof(T))
		bool remove(const T); // O(sizeof(T))
		bool has(const T) const; // O(sizeof(T))
		bool hasAll(T*, size_t size) const; // O(sizeof(T) E) ; O(sizeof(T))
		size_t size();
		class iterator {
		private:
			bool forwards; // O(1)
			T current; // path O(sizeof(T))
			array<trie<T>*> stack; // O(sizeof(T))
		public:
			iterator();
			iterator(bool forwards, trie<T>* root, T current);
			iterator(bool forwards, trie<T>* root);
			iterator(const iterator &original);
			iterator& operator= (const iterator &original);
			bool operator== (const iterator &other);
			bool operator!= (const iterator &other);
			T operator*();
			T operator++();
			T operator--();
			T operator++(int);
			T operator--(int);
		};
		// iterators make read-only bidirectional traversals
		iterator inorder();
		iterator reverseorder();
	};

	#ifndef NULL
	#define NULL 0
	#endif

	template <typename T> typename trie<T>::iterator& trie<T>::iterator::operator= (const iterator &original) {
		forwards = original.forwards;
		stack = original.stack;
		current = original.current;
		return *this;
	}

	template<typename T> trie<T>::iterator::iterator(const iterator &original) {
		forwards = original.forwards;
		stack = original.stack;
		current = original.current;
	}

	template<typename T> trie<T>::iterator::iterator(bool forwards, trie<T>* root, T current) {
		this->forwards = forwards;
		this->stack;
		stack.push_back(root);
		this->current = current;
	}
	template<typename T> trie<T>::iterator::iterator(bool forwards, trie<T>* root) {
		forwards = true;
		stack;
		stack.push_back(root);
		current = 0;
	}
	template<typename T> bool trie<T>::iterator::operator==(const iterator& other) {
		return current == other.current && stack[0] == other.stack[0];
	}
	template<typename T> bool trie<T>::iterator::operator!=(const iterator& other) {
		return current != other.current || stack[0] != other.stack[0];
	}
	template<typename T> T trie<T>::iterator::operator++() {
		// certainly fails in the zero case
		while(!stack.empty()) {
			trie<T>* loc = stack.pop();
			size_t depth = stack.count();
			size_t i = current >> (depth << 2);
			for(++i; i <= 0xF; ++i) {
				if(loc->children[i]) {
					stack.push(loc->children[i]);
					//current = 
					if (loc->children[i]->termination) {
						return *this;
					}
					break;
				}
			}
		}
		// DNF
	}
	template<typename T> T trie<T>::iterator::operator--() {
		return *this;
	}
	template<typename T> T trie<T>::iterator::operator++(int) {
		iterator last = *this;
		return last;
	}
	template<typename T> T trie<T>::iterator::operator--(int) {
		iterator last = *this;
		return last;
	}
	template<typename T> T trie<T>::iterator::operator*() {
		return current;
	}
	template<typename T> bool trie<T>::remove(const T t) {
		if(t == 0) {
			bool change = termination;
			--count;
			termination = false;
			return change;
		}
		else {
			T remains = t >> 4;
			char first = t & 15;
			if (children[first] != NULL) {
				size_t before = children[first]->count;
				bool change = children[first]->remove(remains);
				count -= before - children[first]->count;
				return change;
			}
			return false;
		}
	}
	template<typename T> bool trie<T>::has(const T t) const {
		if(t == 0) {
			return termination;
		}
		else {
			T remains = t >> 4;
			char first = t & 15;
			if (children[first] == NULL) {
				return false;
			}
			return children[first]->has(remains);
		}
	}
	#ifdef PARA
	template<typename T> void* trie<T>::pthreadHas(void* data) {
		pthreadParam* param = data;
		return (void*) param->root->has(*(param->elem));
	}
	#endif
	template<typename T> bool trie<T>::hasAll(T* elements, size_t count) const {
		#ifdef PARA
		bool res = true;
		pthread_t* threadIDs = new pthread_t[count];
		pthreadParam* params = new pthreadParam[count];
		for (size_t i = 0; i < count; ++i) {
			params[i].root = this;
			params[i].elem = &elements[i];
			pthread_create(&threadIDs[i],NULL,(void* (*) (void*)) &(this->pthreadHas),&params[i]);
		}
		for (size_t i = 0; i < count; ++i) {
			pthread_join(threadIDs[i],(void**)&res);
			if (!res) {
				// consider canceling the other threads
				delete[] threadIDs;
				delete[] params;
				return false;
			}
		}
		delete[] threadIDs;
		#else
		for (size_t i = 0; i < count; ++i) {
			if (!has(elements[i])) {
				return false;
			}
		}
		#endif
		return true;
	}
	template<typename T> bool trie<T>::put(const T t) {
		if(t == 0) {
			count++;
			return termination = true;
		}
		else {
			T remains = t >> 4;
			char first = t & 15;
			if (children[first] == NULL) {
				children[first] = new trie<T>;
			}
			size_t before = children[first]->count;
			bool change = children[first]->put(remains);
			count += children[first]->count - before;
			return change;
		}
	}
	template<typename T> trie<T>::trie() {
		size_t max = 16;
		count = 0;
		this->children = new trie<T>*[max];
		for (size_t i = 0; i < max; ++i) {
			this->children[i] = NULL;
		}
		this->termination = false;
	}
	template<typename T> trie<T>::~trie() {
		size_t max = 16;
		for (size_t i = 0; i < max; ++i) {
			if (this->children[i]) {
				delete this->children[i];
			}
		}
	}
	using std::string;
	template <> trie<string>::~trie() {
		size_t max = 1 << 8*sizeof(char);
		for (size_t i = 0; i < max; ++i) {
			if (this->children[i]) {
				delete this->children[i];
			}
		}
	}
	template <> trie<string>::trie() {
		size_t max = 1 << 8*sizeof(char);
		count = 0;
		this->children = new trie<string>*[max];
		for (size_t i = 0; i < max; ++i) {
			this->children[i] = NULL;
		}
		this->termination = false;
	}
	template <> bool trie<string>::put(const string str) {
		if(str.size() == 0) {
			++count;
			return termination = true;
		}
		else {
			string remains = str.substr(1);
			char first = str[0];
			if (children[first] == NULL) {
				children[first] = new trie<string>;
			}
			size_t before = children[first]->count;
			bool change = children[first]->put(remains);
			count += children[first]->count - before;
			return change;
		}
	}
	template <> bool trie<string>::has(const string str) const {
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
	template <> bool trie<string>::remove(const string str) {
		if(str.size() == 0) {
			bool change = termination;
			--count;
			termination = false;
			return change;
		}
		else {
			string remains = str.substr(1);
			char first = str[0];
			if (children[first] != NULL) {
				size_t before = children[first]->count;
				bool change = children[first]->remove(remains);
				count -= before - children[first]->count;
				return change;
			}
			return false;
		}
	}

	template <typename T> size_t trie<T>::size() {
		return count;
	}
}

#endif
