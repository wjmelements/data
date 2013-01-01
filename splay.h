#ifndef splay_w
#define splay_w
#include <cstddef>
namespace data {
	#ifndef NULL
	#define NULL 0
	#endif

	template <typename T> class splaytreenode; 

	template <typename T>
	class splayset {
	private:
		splaytreenode<T>* root;
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
		splaytreenode<tuple>* root;
	public:
		size_t size(); // O(n)
		bool empty(); // O(1)
		void clear(); // O(n)
		V put(K key); // O(log n)
		V get(K key); // O(log n)
		V remove(K key); // O(log n)
	};

	template <typename T>
	class splaytreenode {
	private:
		T data;
		splaytreenode<T>* left;
		splaytreenode<T>* right;
		splaytreenode<T>* up;

		splaytreenode<T>* zigleft();
		splaytreenode<T>* zigright();
		splaytreenode<T>* zigzigleft();
		splaytreenode<T>* zigzigright();
		splaytreenode<T>* zigzagleft();
		splaytreenode<T>* zigzagright();
	public:
		splaytreenode(T elem); // O(1)
		splaytreenode(splaytreenode<T>* parent, T elem);
		size_t size();
		bool has(); // O(log n)
		void insert(T elem); // O(log n)
		void remove(T elem); // O(log n)
	};

	template <typename T> splaytreenode<T>::splaytreenode(T elem) {
		this->data = elem;
		left = NULL;
		right = NULL;
		up = NULL;
	}

	template <typename T> splaytreenode<T>::splaytreenode(splaytreenode<T>* parent, T elem) {
		this->data = elem;
		left = NULL;
		right = NULL;
		up = parent;
	}

	template <typename T> size_t splaytreenode<T>::size() {
		return (left?left->size():0) + (right?right->size():0) + 1;
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigleft() {
		splaytreenode<T>* tosplay = this->right;
		this->right = tosplay->left;
		tosplay->left = this;
		tosplay->up = this->up;
		this->up = tosplay;
		this->right->up = this;
		return this->up;

	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigright() {
		splaytreenode<T>* tosplay = this->left;
		this->left = tosplay->right;
		tosplay->right = this;
		tosplay->up = this->up;
		this->up = tosplay;
		this->left->up = this;
		return this->up;
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzigleft() {
		return zigleft()->zigleft();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzigright() {
		return zigright()->zigright();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzagleft() {
		return right->zigright()->zigleft();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzagright() {
		return left->zigleft()->zigright();
	}
}
#endif
