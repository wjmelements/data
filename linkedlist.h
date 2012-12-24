#ifndef linkedlist_w
#define linkedlist_w

#include "linkedlistnode.h"
#include <cstddef>
using std::size_t;
template <typename T>
class linkedlist
{
private:
	size_t count;
	linkedlistnode<T> first;
	linkedlistnode<T> last;
public:
	linkedlist();
	linkedlist(T first);
	linkedlist(T* elements, size_t size);
	size_t size(); // O(1)
	T at(size_t index); // O(n)
	void push_back(T append); // O(1)
	void push_front(T prepend); // O(1)
	T pop_back(); // O(1)
	T pop_front(); // O(1)
	bool empty(); // O(1)
};
#endif
