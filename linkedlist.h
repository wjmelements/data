#ifndef linkedlist_w
#define linkedlist_w
#include <cstddef>
namespace data {
	using std::size_t;

	template <typename T>
	class linkedlist {
	private:
		class linkedlistnode {
		public:
			T data;
			linkedlistnode* next;
			linkedlistnode* prev;
			linkedlistnode(T data, linkedlistnode* next = NULL);
			linkedlistnode(linkedlistnode* prev, T data, linkedlistnode* next = NULL);
		};
		size_t count;
		linkedlistnode* first;
		linkedlistnode* last;
	public:
		linkedlist(); // O(1)
		linkedlist(T first); // O(1)
		linkedlist(T* elements, size_t size); // O(n)
		linkedlist(const linkedlist<T> &original); // not implemented
		linkedlist<T>& operator= (const linkedlist<T> &original); // not implemented
		size_t size(); // O(1)
		T& front(); // O(1)
		T& back(); // O(1)
		T& at(size_t index); // O(n)
		void push_back(T append); // O(1)
		void push_front(T prepend); // O(1)
		T pop_back(); // O(1)
		T pop_front(); // O(1)
		bool empty(); // O(1)
		void clear(); // O(n)
		class iterator {
		private:
			bool forwards;
			linkedlistnode* current;
		public:
			iterator(); // O(1)
			iterator(bool forwards, linkedlistnode* current); // O(1)
			iterator(const iterator &original); // O(!0
			iterator& operator= (const iterator &original); // O(!0
			bool operator== (const iterator &other); // O(1)
			bool operator!= (const iterator &other); // O(1)
			T& operator* (); // O(1)
			iterator& operator++(); // O(1)
			iterator& operator--(); // O(1)
			iterator operator++(int); // O(1)
			iterator operator--(int); // O(1)
		};
		iterator begin(); // O(1)
		iterator end(); // O(1)
		iterator rbegin(); // O(1)
		iterator rend(); // O(1)
	};

	#ifndef NULL
	#define NULL 0
	#endif

	template<typename E> linkedlist<E>::linkedlistnode::linkedlistnode(E data,linkedlistnode* next) {
		this->data = data;
		this->next = next;
		this->prev = NULL;
	}
	template<typename E> linkedlist<E>::linkedlistnode::linkedlistnode(linkedlistnode* prev,E data,linkedlistnode* next) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
	template <typename T> linkedlist<T>::linkedlist() {
		this->count = 0;
		this->first = NULL;
		this->last = NULL;
	}
	template <typename T> linkedlist<T>::linkedlist(T first) {
		this->count = 1;
		this->first = new linkedlistnode(first);
		this->last = this->first;
	}
	template <typename T> linkedlist<T>::linkedlist(T* elements, size_t size) {
		if (size)
		{
			this->count = 1;
			this->first = new linkedlistnode(elements[0]);
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
	template <typename T> linkedlist<T>::linkedlist<T>(const linkedlist<T> &original) {
		count = 0;
		iterator end = original.end();
		for(iterator it = original.begin(); it != end; ++it) {
			push_back(*it);
		}
	}
	template <typename T> linkedlist<T>& linkedlist<T>::operator= (const linkedlist<T> &original) {
		count  = 0;
		iterator end = original.end();
		for(iterator it = original.begin(); it != end; ++it) {
			push_back(*it);
		}
		return *this;
	}
	template <typename T> size_t linkedlist<T>::size() {
		return count;
	}
	template <typename T> T& linkedlist<T>::front() {
		return this->first->data;
	}
	template <typename T> T& linkedlist<T>::back() {
		return this->last->data;
	}
	template <typename T> void linkedlist<T>::push_back(T elem) {
		linkedlistnode* pushed = new linkedlistnode(this->last,elem);
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
	template <typename T> void linkedlist<T>::push_front(T elem) {
		linkedlistnode* pushed = new linkedlistnode(elem,this->first);
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
	template <typename T> T& linkedlist<T>::at(size_t index) {
		if (index < this->count / 2 )
		{
			linkedlistnode* current = this->first;
			while(index --> 0)
			{
				current = current->next;
			}
			return current->data;
		}
		else
		{
			linkedlistnode* current = this->last;
			while(++index < count)
			{
				current = current->prev;
			}
			return current->data;
		}
	}
	template <typename T> T linkedlist<T>::pop_back() {
		linkedlistnode* popped = this->last;
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
	template <typename T> T linkedlist<T>::pop_front() {
		linkedlistnode* popped = this->first;
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
	template <typename T> bool linkedlist<T>::empty() {
		return count == 0;
	}
	template <typename T> void linkedlist<T>::clear() {
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
	template <typename T> linkedlist<T>::iterator::iterator() {
		forwards = true;
		current = NULL;
	}
	template <typename T> linkedlist<T>::iterator::iterator(bool forwards, linkedlistnode* current) {
		this->forwards = forwards;
		this->current = current;
	}
	template <typename T> linkedlist<T>::iterator& linkedlist<T>::iterator::operator= (const linkedlist<T>::iterator &original) {
		this->forwards = original.forwards;
		this->current = original.current;
	}
	template <typename T> T& linkedlist<T>::iterator::operator* () {
		return this->current->data;
	}
	template <typename T> bool linkedlist<T>::iterator::operator!= (const linkedlist<T>::iterator &other) {
		return this->current != other.current || this->forwards != other.forwards;
	}
	template <typename T> bool linkedlist<T>::iterator::operator== (const linkedlist<T>::iterator &other) {
		return this->current == other.current && this->forwards == other.forwards;
	}
	template <typename T> linkedlist<T>::iterator& linkedlist<T>::iterator::operator++() {
		if (this->forwards) {
			current = current->next;
			return *this;
		}
		else {
			current = current->prev;
			return *this;
		}
	}
	template <typename T> linkedlist<T>::iterator& linkedlist<T>::iterator::operator--() {
		if (this->forwards) {
			current = current->prev;
			return *this;
		}
		else {
			current = current->next;
			return *this;
		}
	}
	template <typename T> linkedlist<T>::iterator linkedlist<T>::iterator::operator++(int) {
		iterator copy(this->forwards,this->current);
		if (this->forwards) {
			current = current->next;
			return copy;
		}
		else {
			current = current->prev;
			return copy;
		}
	}
	template <typename T> linkedlist<T>::iterator linkedlist<T>::iterator::operator--(int) {
		iterator copy(this->forwards,this->current);
		if (this->forwards) {
			current = current->prev;
			return copy;
		}
		else {
			current = current->next;
			return copy;
		}
	}
	template <typename T> linkedlist<T>::iterator linkedlist<T>::begin() {
		return iterator(true,this->first);
	}
	template <typename T> linkedlist<T>::iterator linkedlist<T>::end() {
		return iterator(true,NULL);
	}
	template <typename T> linkedlist<T>::iterator linkedlist<T>::rbegin() {
		return iterator(false,this->last);
	}
	template <typename T> linkedlist<T>::iterator linkedlist<T>::rend() {
		return iterator(false,NULL);
	}
} // namespace data
#endif
