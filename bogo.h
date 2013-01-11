#ifndef bogo_w
#define bogo_w
#include <cstddef>
#include "splay.h"
#include <stdlib.h>
namespace data {
      #ifndef NULL
      #define NULL 0
      #endif

      template <typename T>
      struct bogonode {
            bogonode* up;
            bogonode* left;
            bogonode* right;
            T data;
      };

      template <typename T>
      class bogoweb {
      private:
            bogonode<T>* root;
      public:
            bogoweb();
            bogoweb(T elem);
            void insert(T elem); // unbounded
            bool contains(T elem); // unbounded
      };

      template <typename T> bogoweb<T>::bogoweb() {
            root = NULL;
      }
      template <typename T> bogoweb<T>::bogoweb(T elem) {
            root = new bogonode<T>;
            root->data = elem;
      }
      template <typename T> void bogoweb<T>::insert(T elem) {
            if (root == NULL) {
                  root = new bogonode<T>;
                  root->data = elem;
            }
            else {
                  bool toInsert = true;
                  bogonode<T>* current = root;
                  while (toInsert) {
                        switch(rand() % 3) {
                        case 0: // up
                              if (current->up) {
                                    current = current->up;
                              }
                              else {
                                    current->up = new bogonode<T>;
                                    current->up->data = elem;
                                    if (rand() % 2) {
                                          current->up->right = current;
                                    }
                                    else {
                                          current->up->left = current;
                                    }
                                    toInsert = false;
                              }
                        break;
                        case 1: // left
                              if (current->left) {
                                    current = current->left;
                              }
                              else {
                                    current->left = new bogonode<T>;
                                    current->left->data = elem;
                                    current->left->up = current;
                                    toInsert = false;
                              }
                        case 2: // right
                              if (current->right) {
                                    current = current->right;
                              }
                              else {
                                    current->right = new bogonode<T>;
                                    current->right->data = elem;
                                    current->right->up = current;
                                    toInsert = false;
                              }
                        }
                  }
            }
      }

      template <typename T> bool bogoweb<T>::contains(T elem) {
            // it makes sense to use splay sets here because it will keep local values closer
            if (root == NULL) {
                  return false;
            }
            splayset<bogonode<T>*> toVisit;
            splayset<bogonode<T>*> visited;
            bogonode<T>* current = root;
            do {
                  if (current->data == elem) {
                        return true;
                  }
                  toVisit.remove(current);
                  visited.add(current);
                  if (current->left != NULL) {
                        if (!visited.contains(current->left)) {
                              toVisit.add(current->left);
                        }
                  }
                  if (current->right != NULL) {
                        if (!visited.contains(current->right)) {
                              toVisit.add(current->right);
                        }
                  }
                  if (current->up != NULL) {
                        if (!visited.contains(current->up)) {
                              toVisit.add(current->up);
                        }
                  }
                  switch (rand() % 3) {
                  case 0: // up
                        if (current->up != NULL) {
                              current = current->up;
                        }
                  break;
                  case 1: // left
                        if (current->left != NULL) {
                              current = current->left;
                        }
                  break;
                  case 2: // right
                        if (current->right != NULL) {
                              current = current->right;
                        }
                  break;
                  }
            } while (!toVisit.empty());
            return false;
      }
}
#endif
