#ifndef avl_w
#define avl_w
#include <cstddef>
#include "util.h"
#include "linkedlist.h"

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

namespace data {

	#ifndef NULL
	#define NULL 0
	#endif
	template <typename T> class avltreenode;

	template <typename T>
	class avlset {
	private:
		avltreenode<T>* root;
	public:
		avlset();
		avlset(T elem);
		void add(T elem); // O(log n)
		bool contains(T elem); // O(log n)
		void remove(T elem); // O(log n)
		size_t size(); // O(n)
		size_t height(); // O(1)
		bool empty(); // O(1)
		void clear(); // O(n)
			#ifdef DEBUG
			void sanityCheck();
			#endif
	};

	template <typename K, typename V>
	class avlmap {
	private:
		struct tuple {
			K key;
			V value;
			bool operator< (const tuple& other);
			bool operator== (const tuple& other);
		};
		avltreenode<tuple>* root;
	public:
		avlmap();
		avlmap(K key, V value);
		void put(K key, V value); // O(log n)
		V get(K key); // O(log n)
		void remove(K key); // O(log n)
		size_t size(); // O(n)
		size_t height(); // O(1)
		bool empty(); // O(1)
		void clear(); // O(n)
		#ifdef DEBUG
		void sanityCheck();
		#endif
	};

	template <typename T>
	class avltreenode {
	private:
		avltreenode<T>* left;
		avltreenode<T>* right;
		size_t leftHeight;
		size_t rightHeight;
		avltreenode<T>* rotateLeft();
		avltreenode<T>* rotateRight();
	public:
		T data;
		avltreenode(T elem);
		avltreenode<T>* insert(T elem);
		avltreenode<T>* find(T elem);
		bool contains(T elem);
		avltreenode<T>* remove(T elem);
		#ifdef DEBUG
		void sanityCheck();
		#endif
	};

	template <typename T> avltreenode<T>* avltreenode<T>::rotateLeft() {
		avltreenode<T>* root = right;
		right = root->left;
		root->left = this;
		this->rightHeight = root->leftHeight;
		root->leftHeight = 1 + max(this->leftHeight,this->rightHeight);
		return root;
	}

	template <typename T> avltreenode<T>* avltreenode<T>::rotateRight() {
		avltreenode<T>* root = left;
		left = root->right;
		root->right = this;
		this->leftHeight = root->rightHeight;
		root->rightHeight = 1 + max(this->leftHeight,this->rightHeight);
		return root;
	}

	template <typename T> avltreenode<T>::avltreenode(T elem) {
		data = elem;
		left = NULL;
		right = NULL;
		leftHeight = 0;
		rightHeight = 0;
	}

	template <typename T> avltreenode<T>* avltreenode<T>::insert(T elem) {
		if (elem < this->data) {
			if (left) {
				left = left->insert(elem);
				leftHeight = max(left->leftHeight,left->rightHeight) + 1;
				if (leftHeight > 1 + rightHeight) {
					if (left->leftHeight < left->rightHeight) {
						left = left->rotateLeft();
					}
					return rotateRight();
				}
				return this;
			}
			else {
				left = new avltreenode(elem);
				leftHeight = 1;
				return this;
			}
		}
		if (elem == this->data) {
			data = elem;
			return this;
		}
		if (right) {
			right = right->insert(elem);
			rightHeight = max(right->rightHeight,right->leftHeight) + 1;
			if (rightHeight > 1 + leftHeight) {
				if (right->rightHeight < right->leftHeight) {
					right = right->rotateRight();
				}
				return rotateLeft();
			}
			return this;
		}
		else {
			right = new avltreenode(elem);
			rightHeight = 1;
			return this;
		}
	}

	template <typename T> avltreenode<T>* avltreenode<T>::find(T elem) {
		if (elem < data) {
			if (left) {
				return left->find(elem);
			}
			else {
				return NULL;
			}
		}
		if (elem == data) {
			return this;
		}
		if (right) {
			return right->find(elem);
		}
		return NULL;

	}

	template <typename T> bool avltreenode<T>::contains(T elem) {
		if (elem < data) {
			if (left) {
				return left->contains(elem);
			}
			else {
				return false;
			}
		}
		if (elem == data) {
			return true;
		}
		if (right) {
			return right->contains(elem);
		}
		return false;
	}

	template <typename T> avlset<T>::avlset() {
		root = NULL;
	}

	template <typename T> avlset<T>::avlset(T elem) {
		root = new avltreenode<T>(elem);
	}

	template <typename T> void avlset<T>::add(T elem) {
		if (root) {
			root = root->insert(elem);
		}
		else {
			root = new avltreenode<T>(elem);
		}
		#ifdef DEBUG
		sanityCheck();
		#endif
	}

	template <typename T> bool avlset<T>::contains(T elem) {
		#ifdef DEBUG
		sanityCheck();
		#endif
		if (root) {
			return root->contains(elem);
		}
		return false;
	}

	template <typename K, typename V> avlmap<K,V>::avlmap() {
		root = NULL;
	}

	template <typename K, typename V> avlmap<K,V>::avlmap(K key, V value) {
		tuple map;
		map.key = key;
		map.value = value;
		root = new avltreenode<tuple>(map);
	}

	template <typename K, typename V> void avlmap<K,V>::put(K key, V value) {
		tuple map;
		map.key = key;
		map.value = value;
		if (root) {
			root = root->insert(map);
		}
		else {
			root = new avltreenode<tuple>(map);
		}
		#ifdef DEBUG
		sanityCheck();
		#endif
	}

	template <typename K,typename V> V avlmap<K,V>::get(K key) {
		#ifdef DEBUG
		sanityCheck();
		#endif
		if (root == NULL) {
			return NULL;
		}
		tuple map;
		map.key = key;
		return root->find(map)->data.value;
	}

	template <typename K,typename V> bool avlmap<K,V>::tuple::operator< (const tuple& other) {
		return key < other.key;
	}

	template <typename K,typename V> bool avlmap<K,V>::tuple::operator== (const avlmap<K,V>::tuple& other) {
		return key == other.key;
	}

	template <typename T> void avlset<T>::remove(T elem) {
		if (root) {
			root = root->remove(elem);
		}
	}

	template <typename K, typename V> void avlmap<K,V>::remove(K key) {
		if (root) {
			tuple find;
			find.key = key;
			root = root->remove(find);
		}
	}


	template <typename T> avltreenode<T>* avltreenode<T>::remove(T elem) {
		if (elem < data) {
			if (left) {
				if (left = left->remove(elem)) {
					leftHeight = 1 + max(left->leftHeight,left->rightHeight);
				}
				else {
					leftHeight = 0;
				}
				if (rightHeight > 1 + leftHeight) {
					if (right->rightHeight < right->leftHeight) {
						right = right->rotateRight();
					}
					return rotateLeft();
				}
			}
			return this;
		}
		if (elem == data) {
			if (left) {
				if (right) {
					// find next inorder node
					avltreenode<T>* swap = right;
					linkedlist<avltreenode<T>*> stack;
					while (swap->left != NULL) {
						stack.push_back(swap);
						swap = swap->left;
					}
					this->data = swap->data;
					if (stack.empty()) {
						right = right->right;
						--rightHeight;
						if (leftHeight - rightHeight > 1) {
							if (left->right && left->left == NULL) {
								left = left->rotateLeft();
							}
							return rotateRight();
						}
						return this;
					}
					// removal
					avltreenode<T>* pre = stack.pop_back();
					pre->left = swap->right;
					pre->leftHeight--;
					// adjustment
					while (!stack.empty()) {
						pre = stack.pop_back();
						pre->leftHeight = 1 + max(pre->left->leftHeight,pre->left->rightHeight);
						if (pre->left->rightHeight - pre->left->leftHeight > 1) {
							if (pre->left->right->leftHeight > pre->left->right->rightHeight) {
								pre->left->right = pre->left->right->rotateLeft();
							}
							pre->left = pre->left->rotateLeft();
						}
					}
					// pre is now right
					if (right->rightHeight - right->leftHeight > 1) {
						if (right->right->leftHeight - right->right->rightHeight > 1) {
							right->right = right->right->rotateRight();
						}
						right = right->rotateLeft();
					}
					rightHeight = 1 + max(right->leftHeight,right->rightHeight);
					if (leftHeight - rightHeight > 1) {
						if (left->rightHeight - left->leftHeight > 1) {
							left = left->rotateLeft();
						}
						return rotateRight();
					}
					return this;
				}
				else {
					return left;
				}
			}
			else {
				return right;
			}
		}
		if (right) {
			if (right) {
				if (right = right->remove(elem)) {
					rightHeight = 1 + max(right->leftHeight,right->rightHeight);
				}
				else {
					rightHeight = 0;
				}
				if (leftHeight > 1 + rightHeight) {
					if (left->leftHeight < left->rightHeight) {
						left = left->rotateLeft();
					}
					return rotateRight();
				}
			}
		}
		return this;
	}

	#ifdef DEBUG
	template <typename T> void avlset<T>::sanityCheck() {
		if (root) {
			root->sanityCheck();
		}
	}

	template <typename K,typename V> void avlmap<K,V>::sanityCheck() {
		if (root) {
			root->sanityCheck();
		}
	}

	template <typename T> void avltreenode<T>::sanityCheck() {
		if (leftHeight > rightHeight + 1) {
			cout << "Left Height is too large" << leftHeight << rightHeight << endl;
		}
		else if (rightHeight > leftHeight + 1) {
			cout << "Right height is too large:" << rightHeight << leftHeight << endl;
		}
		if (left) {
			left->sanityCheck();
			if (leftHeight != max(left->leftHeight,left->rightHeight) + 1) {
				cout << "leftHeight is " << leftHeight << " but should be " << max(left->leftHeight,left->rightHeight) + 1 << endl;
			}
		}
		else {
			if (leftHeight != 0) {
				cout << "leftHeight is not 0 but left node is NULL" << endl;
			}
		}
		if (right) {
			right->sanityCheck();
			if (rightHeight != max(right->rightHeight,right->leftHeight) + 1) {
				cout << "rightHeight is " << rightHeight << " but should be " << max(right->rightHeight,right->leftHeight) + 1 << endl;
			}
		}
	}
	#endif

}
#endif
