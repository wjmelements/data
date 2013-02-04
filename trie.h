#ifndef trie_w
#define trie_w

#include <cstddef>
#include <string>

#ifdef PARA
#include <pthread.h>
#endif

namespace data {
	/*
		supported types:
		string
		(un)signed long long
		(un)signed long
		(un)signed int
		(un)signed short
		(un)signed char
	*/
	template <typename T>
	class trie {
	private:
		trie<T>** children;
		bool termination;
		#ifdef PARA
		static void* pthreadHas(void*);
		struct pthreadParam {
			trie<T>* root;
			T* elem;
		};
		#endif

	public:
		trie(); // O(sizeof(T))
		void put(const T); // O(sizeof(T))
		void remove(const T); // O(sizeof(T))
		bool has(const T) const; // O(sizeof(T))
		bool hasAll(T*, size_t size) const; // O(sizeof(T) E) ^ O(sizeof(T))
		size_t count();
		class iterator {
		private:
			bool forwards;
			trie<T>* root;
			T current;
		public:
			iterator();
			iterator(bool forwards, trie<T>* root, T current);
			iterator(const iterator &original);
			iterator& operator= (const iterator &original);
			bool operator== (const iterator &other);
			bool operator!= (const iterator &other);
			T operator*();
			iterator& operator++();
			iterator& operator--();
			iterator operator++(int);
			iterator operator--(int);
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
		root = original.root;
		current = original.current;
		return *this;
	}

	template<typename T> trie<T>::iterator::iterator(const iterator &original) {
		forwards = original.forwards;
		root = original.root;
		current = original.current;
	}

	template<typename T> trie<T>::iterator::iterator(bool forwards, trie<T>* root, T current) {
		this->forwards = forwards;
		this->root = root;
		this->current = current;
	}
	template<typename T> trie<T>::iterator::iterator() {
		forwards = true;
		root = NULL;
		current = 0;
	}
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
	template<typename T> bool trie<T>::has(const T t) const {
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
	#ifdef PARA
	template<typename T> static void* trie<T>::pthreadHas(void* data) {
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
			pthread_create(&threadIDs[i],NULL,(void* (*) (void*))&(this->pthreadHas),&params[i]);
		}
		for (size_t i = 0; i < count; ++i) {
			pthread_join(threadIDs[i],(void**)&res);
			if (!res) {
				// consider canceling the other threads
				delete threadIDs;
				return false;
			}
		}
		delete threadIDs;
		#else
		for (size_t i = 0; i < count; ++i) {
			if (!has(elements[i])) {
				return false;
			}
		}
		#endif
		return true;
	}
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
	template<typename T> trie<T>::trie() {
		size_t max = 16;
		this->children = new trie<T>*[max];
		for (size_t i = 0; i < max; ++i) {
			this->children[i] = NULL;
		}
		this->termination = false;
	}
	
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
}

#endif
