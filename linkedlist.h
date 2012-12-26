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
		this->last = this->last->next = pushed;
	}
	else
	{
		this->last = this->first = pushed;
	}
	this->count++;
}
template <typename T> void linkedlist<T>::push_front(T elem)
{
	linkedlistnode<T>* pushed = new linkedlistnode<T>(elem,this->first);
	if(this->count)
	{
		this->first = this->first->prev = pushed;
	}
	else
	{
		this->first = this->last = pushed;
	}
	this->count++;
}
template <typename T> T linkedlist<T>::at(size_t index)
{
	if (index < this->count / 2 )
	{
		linkedlistnode<T>* current = this->first;
		while(index --> 0)
		{
			current = current->next;
		}
		return current->data;
	}
	else
	{
		linkedlistnode<T>* current = this->last;
		while(++index < count)
		{
			current = current->prev;
		}
		return current->data;
	}
}
#endif
