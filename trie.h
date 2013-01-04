#ifndef trie_w
#define trie_w

#include <cstddef>

#ifndef NULL
#define NULL 0
#endif
namespace data {
	/*
		implemented types:
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
	public:
		trie(); // O(sizeof(T))
		void put(const T); // O(sizeof(T))
		void remove(const T); // O(sizeof(T))
		bool has(const T); // O(sizeof(T))
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
}

#endif
