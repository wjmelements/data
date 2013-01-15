#ifndef rb_w
#define rb_w
#include <cstddef>
namespace data {

	template <typename T> class rbtreenode;

	template <typename T> class rbset {
	private:
		rbtreenode<T>* root;
	public:
		rbset();
		size_t size();
		bool empty();
		void clear();
		void add(T elem);
		void remove(T elem);
		bool contains(T elem);
	};

	template <typename K, typename V> class rbmap {
	private:
		struct tuple {
			K key;
			V value;
			bool operator== (tuple& other);
			bool operator< (tuple& other);
		};
		rbtreenode<tuple>* root;
	public:	
		rbmap();
		size_t size();
		bool empty();
		void clear();
		
	};

	template <typename T> class rbtreenode {
	private:
		rbtreenode<T>* left;
		rbtreenode<T>* right;
		T data;
		bool isRed;
	public:
		rbtreenode(T elem);
		bool has(T elem);
	};
}
#endif
