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
		size_t size(); // O(1)
		void clear(); // O(n)
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
		while (data[current] > elem && current) {
			data[last] = data[current];
			last = current;
			current >>= 1;
		}
		data[last] = elem;
	}

	template <typename T> T beap<T>::pop() {
		if (count == 0) {
			return NULL;
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

	template <typename T> size_t beap<T>::size() {
		return count;
	}

	template <typename T> void beap<T>::clear() {
		count = 0;
		delete[] data;
		maxSize = defaultSize;
		data = new T[maxSize];
	}

} // namespace data
#endif
