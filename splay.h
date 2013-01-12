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
		splayset();
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
			bool operator== (tuple& other);
			bool operator< (tuple& other);
		};
		splaytreenode<tuple>* root;
	public:
		splaymap();
		size_t size(); // O(n)
		bool empty(); // O(1)
		void clear(); // O(n)
		void put(K key, V value); // O(log n)
		V get(K key); // O(log n)
		void remove(K key); // O(log n)
	};

	template <typename T>
	class splaytreenode {
	private:
		splaytreenode<T>* left;
		splaytreenode<T>* right;
		splaytreenode<T>* up;

		splaytreenode<T>* zigleft();
		splaytreenode<T>* zigright();
		splaytreenode<T>* zigzigleft();
		splaytreenode<T>* zigzigright();
		splaytreenode<T>* zigzagleft();
		splaytreenode<T>* zigzagright();
		splaytreenode(splaytreenode<T>* parent, T elem);
	public:
		T data;

		splaytreenode(T elem); // O(1)
		size_t size(); // O(n)
		splaytreenode<T>* find(T elem); // O(log n)
		splaytreenode<T>* insert(T elem); // O(log n)
		splaytreenode<T>* remove(T elem); // O(log n)
		splaytreenode<T>* splay(); // O(log n)
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
		if (tosplay->up != NULL) {
			if (tosplay->up->left == this) {
				tosplay->up->left = tosplay;
			}
			else {
				tosplay->up->right = tosplay;
			}
		}
		this->up = tosplay;
		if (this->right != NULL) {
			this->right->up = this;
		}
		return tosplay;

	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigright() {
		splaytreenode<T>* tosplay = this->left;
		this->left = tosplay->right; // here
		tosplay->right = this;
		tosplay->up = this->up;
		if (tosplay->up != NULL) {
			if (tosplay->up->left == this) {
				tosplay->up->left = tosplay;
			}
			else {
				tosplay->up->right = tosplay;
			}
		}
		this->up = tosplay;
		if (this->left != NULL) {
			this->left->up = this;
		}
		return tosplay;
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzigleft() {
		return zigleft()->zigleft();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzigright() {
		return zigright()->zigright();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzagleft() {
            right->zigright();
		return zigleft();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::zigzagright() {
            left->zigleft();
		return zigright();
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::find(T elem) {
		if (elem < this->data) {
			if (left) {
				return left->find(elem);
			}
			else {
				return NULL;
			}
		}
		if (elem == this->data) {
			return this;
		}
		else {
			if (right) {
				return right->find(elem);
			}
			else {
				return NULL;
			}
		}
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::insert(T elem) {
		if (elem < this->data) {
			if (left != NULL) {
				return left->insert(elem);
			}
			else {
				left = new splaytreenode<T>(this,elem);
				return left;
			}
		}
		if (elem == this->data) {
			this->data = elem;
			return this;
		}
		else {
			if (right != NULL) {
				return right->insert(elem);
			}
			else {
				right = new splaytreenode<T>(this,elem);
				return right;
			}
		}
	}

	template <typename T> splaytreenode<T>* splaytreenode<T>::splay() {
		if (this->up == NULL) {
			return this; // done
		}
		splaytreenode<T>* parent = this->up;
		bool wasLeft = parent->left == this;
		splaytreenode<T>* grandparent = parent->up;
		if (grandparent == NULL) {
			if (wasLeft) {
				return parent->zigright();
			}
			else {
				return parent->zigleft();
			}
		}
		bool wasFirstLeft = grandparent->left && (wasLeft?
			grandparent->left->left == this :
			grandparent->left->right == this);
		if (wasFirstLeft) {
			if (wasLeft) {
				return grandparent->zigzigright()->splay();
			}
			else {
				return grandparent->zigzagright()->splay();
			}
		}
		else {
			if (wasLeft) {
				return grandparent->zigzagleft()->splay();
			}
			else {
				return grandparent->zigzigleft()->splay();
			}
		}
	}

	template <typename T> splayset<T>::splayset() {
		root = NULL;
	}

	template <typename T> size_t splayset<T>::size() {
		if (root == NULL) {
			return 0;
		}
		return root->size();
	}

	template <typename T> bool splayset<T>::empty() {
		return root == NULL;
	}

	template <typename T> void splayset<T>::clear() {
		delete root;
		root = NULL;
	}

	template <typename T> void splayset<T>::add(T elem) {
		if (root == NULL) {
			root = new splaytreenode<T>(elem);
		}
		else {
			root = root->insert(elem)->splay();
		}
	}

	template <typename T> bool splayset<T>::contains(T elem) {
		if (root == NULL) {
			return false;
		}
		else {
			splaytreenode<T>* loc = root->find(elem);
			if (loc == NULL) {
				return false;
			}
			else {
				root = loc->splay();
				return true;
			}
		}
	}

      template <typename T> splaytreenode<T>* splaytreenode<T>::remove(T elem) {
            splaytreenode<T>* loc = find(elem);
            if (loc == NULL) {
                  return this;
            }
            loc->splay();
            splaytreenode<T>* rightsub = loc->right;
            splaytreenode<T>* leftsub = loc->left;
            if (leftsub == NULL) {
                  if (rightsub != NULL) {
                        rightsub->up = NULL;
                  }
                  return rightsub;
            }
            leftsub->up = NULL;
            splaytreenode<T>* root = leftsub;
            while (root->right != NULL) {
                  root = root->right;
            }
            root->splay();
            if (rightsub != NULL) {
                  root->right = rightsub;
                  rightsub->up = root;
            }
            return root;
      }

      template <typename K, typename V> void splaymap<K,V>::remove(K key) {
            if (root != NULL) {
                  tuple elem;
                  elem.key = key;
                  root = root->remove(elem);
            }
      }

      template <typename T> void splayset<T>::remove(T elem) {
            if (root != NULL) {
                  root = root->remove(elem);
            }
      }

	template <typename K, typename V> bool splaymap<K,V>::tuple::operator== (tuple& other) {
		return key == other.key;
	}

	template <typename K, typename V> bool splaymap<K,V>::tuple::operator< (tuple& other) {
		return key < other.key;
	}

	template <typename K,typename V> splaymap<K,V>::splaymap() {
		root = NULL;
	}

	template <typename K,typename V> size_t splaymap<K,V>::size() {
		if (root == NULL) {
			return 0;
		}
		else {
			return root->size();
		}
	}

	template <typename K, typename V> bool splaymap<K,V>::empty() {
		return root == NULL;
	}

	template <typename K, typename V> void splaymap<K,V>::clear() {
		delete root;
		root = NULL;
	}

	template <typename K, typename V> void splaymap<K,V>::put(K key, V value) {
		tuple pair;
		pair.key = key;
		pair.value = value;
		if (root == NULL) {
			tuple pair;
			pair.key = key;
			pair.value = value;
			root = new splaytreenode<tuple>(pair);
		}
		else {
			root = root->insert(pair)->splay();
		}
	}

	template <typename K, typename V> V splaymap<K,V>::get(K key) {
		tuple pair;
		pair.key = key;
		if (root == NULL) {
			return NULL;
		}
		splaytreenode<tuple>* loc = root->find(pair);
		if (loc) {
			root = loc->splay();
			return loc->data.value;
		}
		return NULL;
		
	}
}
#endif
