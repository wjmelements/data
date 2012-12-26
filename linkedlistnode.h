#ifndef linkedlistnode_w
#define linkedlistnode_w

#ifndef NULL
#define NULL 0
#endif

template<typename E> class linkedlist;

template<typename E> class linkedlistnode
{
private:
	E data;
	linkedlistnode<E>* prev;
	linkedlistnode<E>* next;
public:
	linkedlistnode(E data, linkedlistnode<E>* next = NULL);
	linkedlistnode(linkedlistnode<E>* prev, E data, linkedlistnode<E>* next = NULL);
	friend class linkedlist<E>;
};

template<typename E> linkedlistnode<E>::linkedlistnode(E data,linkedlistnode<E>* next)
{
	this->data = data;
	this->next = next;
	this->prev = NULL;
}
template<typename E> linkedlistnode<E>::linkedlistnode(linkedlistnode<E>* prev,E data,linkedlistnode<E>* next)
{
	this->data = data;
	this->next = next;
	this->prev = prev;
}

#endif
