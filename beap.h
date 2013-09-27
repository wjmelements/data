#ifndef BEAP_W
#define BEAP_W
#include <cstring>
#include <cstddef>

namespace data {

	// the name beap should have caught on; binary heap is long and heap is ambiguous

	template <typename T>
	class beap {
	private:
		T* data;
		size_t count;
		size_t maxSize;
		void doubleSize();
		static const size_t defaultSize = 4;
	public:
		beap(); // O(1)
		beap(const T& elem); // O(1)
		beap(T* array, size_t count); // O(n log n)
		~beap();
		void insert(const T& elem); // O(log n)
		T pop(); // O(log n)
		size_t size() const; // O(1)
		void clear(); // O(n)
	};

	template <typename P,typename T>
	class priorityq {
	private:
		struct tuple {
			P priority;
			T data;
			bool operator< (const tuple& other) const;
		};
		beap<tuple>* data;
	public:	
		priorityq();
		priorityq(P* priorities, T* elements, size_t count);
		~priorityq();
		void insert(P priority, T data);
		T pop();
		size_t size() const;
		void clear();
	};

	template <typename T> beap<T>::beap() {
		count = 0;
		maxSize = defaultSize;
		data = new T[maxSize];
	}

	template <typename T> beap<T>::beap(const T& elem) {
		count = 1;
		maxSize = defaultSize;
		data = new T[maxSize];
		data[count] = elem;
	}

	template <typename T> beap<T>::beap(T* array, size_t starting_count) {
		maxSize = defaultSize;
		while (starting_count >= maxSize) {
			maxSize <<= 1;
		}
		count = 0;
		data = new T[maxSize];
		for (size_t index = 0; index < starting_count; ++index) {
			insert(array[index]);
		}
	}

	template <typename T> beap<T>::~beap() {
		delete[] data;
	}

	template <typename T> void beap<T>::doubleSize() {
		T* copy = new T[maxSize <<= 1];
		memcpy(copy,data,count*sizeof(T));
		data = copy;
	}

	template <typename T> void beap<T>::insert(const T& elem) {
		if (maxSize == ++count) {
			doubleSize();
		}
		size_t current = count >> 1;
		size_t last = count;
		while (elem < data[current] && current) {
			data[last] = data[current];
			last = current;
			current >>= 1;
		}
		data[last] = elem;
	}

	template <typename T> T beap<T>::pop() {
		if (count == 0) {
			return (T) NULL;
		}
		size_t current = 1;
		size_t left = 2;
		size_t right = 3;
		T popped = data[current];
		while ((left < count && data[count] > data[left]) || (right < count && data[count] > data[right])) {
			if (data[left] < data[right]) {
				data[current] = data[left];
				current = left;
			}
			else {
				data[current] = data[right];
				current = right;
			}
			left = current << 1;
			right = left | 1;
		}
		data[current] = data[count];
		--count;
		return popped;
	}

	template <typename T> size_t beap<T>::size() const {
		return count;
	}

	template <typename T> void beap<T>::clear() {
		count = 0;
		delete[] data;
		maxSize = defaultSize;
		data = new T[maxSize];
	}

	template <typename P, typename T> priorityq<P,T>::priorityq() {
		data = new beap<tuple>();
	}
	template <typename P, typename T> priorityq<P,T>::priorityq(P* priorities, T* elements, size_t count) {
		data = new beap<tuple>();
		for (size_t i = 0; i < count; ++i) {
			tuple pair;
			pair.priority = priorities[i];
			pair.data = elements[i];
			data->insert(pair);
		}
	}
	template <typename P, typename T> priorityq<P,T>::~priorityq() {
		delete data;
	}
	template <typename P, typename T> void priorityq<P,T>::insert(P priority, T value) {
		tuple pair;
		pair.priority = priority;
		pair.data = value;
		data->insert(pair);
	}
	template <typename P, typename T> T priorityq<P,T>::pop() {
		return data->pop().data;
	}
	template <typename P, typename T> size_t priorityq<P,T>::size() const {
		return data->size();
	}
	template <typename P, typename T> void priorityq<P,T>::clear() {
		data->clear();
	}

	template <typename P, typename T> bool priorityq<P,T>::tuple::operator< (const tuple& other) const {
		return priority < other.priority;
	}

} // namespace data
#endif
