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
	linkedlistnode<T>* first;
	linkedlistnode<T>* last;
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

template <typename T> linkedlist<T>::linkedlist()
{
	this->count = 0;
	this->first = NULL;
	this->last = NULL;
}
template <typename T> linkedlist<T>::linkedlist(T first)
{
	this->count = 1;
	this->first = new linkedlistnode<T>(first);
	this->last = this->first;
}
template <typename T> linkedlist<T>::linkedlist(T* elements, size_t size)
{
	if (size)
	{
		this->count = 1;
		this->first = new linkedlistnode<T>(elements[0]);
		this->last = this->first;
		while(this->count < size)
		{
			push_back(elements[this->count]);
		}
	}
	else
	{
		this->count = 0;
		this->first = NULL;
		this->last = NULL;
	}
}
template <typename T> void linkedlist<T>::push_back(T elem)
{
	linkedlistnode<T>* pushed = new linkedlistnode<T>(this->last,elem);
	if(this->count)
	{
		this->last->next = pushed;
		this->last = pushed;
	}
	else
	{
		this->last = pushed;
		this->first = this->last;
	}
	this->count++;
}
template <typename T> T linkedlist<T>::at(size_t index)
{
	linkedlistnode<T>* current = this->first;
	while(index)
	{
		current = current->next;
		index--;
	}
	return *(current->data);
}
#endif
