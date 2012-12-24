template<typename E> class linkedlistnode
{
private:
	E data;
	linkedlistnode<E> prev;
	linkedlistnode<E> next;
public:
	linkedlistnode(const E data);
};

