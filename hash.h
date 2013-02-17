#ifndef hash_w
#define hash_w
namespace data {

	template <typename T> size_t hash(T value);
	
	template <typename T> class hashset {
	private:
		void doubleSize();
	public:
		hashset();
		hashset(size_t capacity, float loadFactor);
		bool add(T elem);
		bool contains(T elem);
		bool isEmpty();
		size_t size();
	}

	template <typename K, typename V> class hashmap {
	private:
		void doubleSize();
	public:
		hashmap();
		hashmap(size_t capacity);
		hashmap(size_t capacity, float loadFactor);
		V get(K key);
		void put(K key, V value);
		size_t size();
	}
}
#endif
