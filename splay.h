#ifndef splay_w
#define splay_w
#include <cstddef>
namespace data {
	#ifndef NULL
	#define NULL 0
	#endif

	template <typename T> class splaytree; 

	template <typename T>
	class splayset {
	private:
		splaytree<T>* root;
	public:
		size_t size(); // O(n)
		bool empty(); // O(1)
		void clear(); // O(n)
		void add(T elem); // O(log n)
		void remove(T elem); // O(log n)
		bool contains(T elem); // O(log n)
	};

	template <typename K, typename V>
	class splaymap {
	private:
		struct tuple {
			K key;
			V value;
		};
		splaytree<tuple>* root;
	public:
		size_t size(); // O(n)
		bool empty(); // O(1)
		void clear(); // O(n)
		V put(K key); // O(log n)
		V get(K key); // O(log n)
		V remove(K key); // O(log n)
	};

	template <typename T>
	class splaytree {
	private:
		T data;
		splaytree* left;
		splaytree* right;
	public:
		bool has(); // O(log n)
		void insert(T elem); // O(log n)
		void remove(T elem); // O(log n)
	};
	
}
#endif
