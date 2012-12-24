#ifndef NULL
#define NULL 0
#endif
template<typename E> class linkedlistnode
{
private:
	E* data;
	linkedlistnode<E>* prev;
	linkedlistnode<E>* next;
public:
	linkedlistnode(E data);
};
template<typename E> linkedlistnode<E>::linkedlistnode(E data)
{
	this->data = &data;
	this->next = NULL;
	this->prev = NULL;
}
