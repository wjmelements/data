#ifndef trie_w
#define trie_w

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
		trie();
		void put(const T); // O(sizeof(T))
		void remove(const T); // O(sizeof(T))
		bool has(const T); // O(sizeof(T))
	};
}

#endif
