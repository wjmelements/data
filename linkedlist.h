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
	linkedlist(); // O(1)
	linkedlist(T first); // O(1)
	linkedlist(T* elements, size_t size); // O(n)
	size_t size(); // O(1)
	T at(size_t index); // O(n)
	void push_back(T append); // O(1)
	void push_front(T prepend); // O(1)
	T pop_back(); // O(1)
	T pop_front(); // O(1)
	bool empty(); // O(1)
	void clear(); // O(n)
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
template <typename T> size_t linkedlist<T>::size() {
	return count;
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
template <typename T> T linkedlist<T>::pop_back()
{
	linkedlistnode<T>* popped = this->last;
	this->last = popped->prev;
	if (this->last == NULL)
	{
		this->first = NULL;
	}
	else
	{
		this->last->next = NULL;
	}
	count--;
	T data = popped->data;
	delete popped;
	return data;
}
template <typename T> T linkedlist<T>::pop_front()
{
	linkedlistnode<T>* popped = this->first;
	this->first = popped->next;
	if (this->first == NULL)
	{
		this->last = NULL;
	}
	else
	{
		this->first->prev = NULL;
	}
	count--;
	T data = popped->data;
	delete popped;
	return data;
}
template <typename T> bool linkedlist<T>::empty()
{
	return count == 0;
}
template <typename T> void linkedlist<T>::clear()
{
/*	while(count) {
		this->pop_front();
	}*/
	if (count) {
		while(this->first->next) {
			this->first = this->first->next;
			delete this->first->prev;
		}
		delete this->last;
		this->first = this->last = NULL;
		count = 0;
	}
}
#endif
