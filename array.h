#ifndef array_w
#define array_w
namespace data {

	template <typename T> class array {
	private:
		size_t prebuffer;
		size_t postbuffer;
		size_t size;
		T* data;
		void tripleSize(); // amoritized O(1)
		static const size_t INITIAL_BUFFER = 10;
	public:
		array(); // O(1)
		array(size_t initialBuffer); // O(n)
		array(const T* start, size_t count); // O(n)
		~array();
		T& operator[](const int index); // O(1)
		T get(const int index); // O(1)
		void push_back(const T& elem); // amoritized O(1)
		void push_front(const T& elem); // amoritized O(1)
		T pop_back(); // O(1)
		T pop_front(); // O(1)
		void insert(const size_t index, const T& elem); // O(n)
		size_t count(); // O(1)
		void compact(); // O(n)
		void clear(); // O(1)
	};

	template <typename T> void array<T>::tripleSize() {
		postbuffer = (prebuffer + postbuffer + size);
		T* remake = new T[3*postbuffer];
		remake += postbuffer;
		// copy the old material into the new storage
		for(size_t i = 0; i < size; ++i) {
			remake[i] = data[i];
		}
		data -= prebuffer; // excluding this line causes a segmentation fault
		delete[]data;
		prebuffer = postbuffer;
		data = remake;
	}

	template <typename T> array<T>::array() {
		size = 0;
		prebuffer = postbuffer = INITIAL_BUFFER;
		data = new T[prebuffer << 2];
		data += INITIAL_BUFFER;
	}

	template <typename T> array<T>::array(size_t initialBuffer) {
		size = 0;
		prebuffer = postbuffer = initialBuffer;
		data = new T[prebuffer << 2];
		data += prebuffer;
	}

	template <typename T> array<T>::~array() {
		data -= prebuffer;
		delete[] data;
	}

	template <typename T> array<T>::array(const T* start, size_t count) {
		prebuffer = postbuffer = size = count;
		data = new T[count * 3];
		data += count;
		for (size_t i = 0; i < count; ++i) {
			data[i] = start[i];
		}
	}

	template <typename T> T& array<T>::operator[](const int index) {
		return data[index];
	}

	template <typename T> T array<T>::get(const int index) {
		return data[index];
	}

	template <typename T> void array<T>::push_back(const T& elem) {
		if (postbuffer == 0) {
			tripleSize();
		}
		data[size++] = elem;
		postbuffer--;
	}

	template <typename T> void array<T>::push_front(const T& elem) {
		if (prebuffer == 0) {
			tripleSize();
		}
		*(--data) = elem;
		size++;
		prebuffer--;
	}


	template <typename T> T array<T>::pop_back() {
		postbuffer++;
		return data[--size];
	}

	template <typename T> T array<T>::pop_front() {
		prebuffer++;
		return *(data++);
	}

	template <typename T> void array<T>::insert(const size_t index, const T& elem) {
		if (index > size >> 1) {
			if (postbuffer == 0) {
				tripleSize();
			}
			postbuffer--;
			size++;
			for (int i = size; i > index; --i) {
				data[i] = data[i - 1];
			} // make way
			data[index] = elem;
		} // forwards
		else {
			if (prebuffer == 0) {
				tripleSize();
			}
			prebuffer--;
			size++;
			data--;
			for (int i = 0; i < index; ++i) {
				data[i] = data[i + 1];
			}
			data[index] = elem;
		} // backwards
	}

	template <typename T> size_t array<T>::count() {
		return size;
	}

	template <typename T> void array<T>::compact() {
		T* remake = new T[size];
		for (size_t i = 0; i < size; ++i) {
			remake[i] = data[i];
		}
		data -= prebuffer;
		delete[] data;
		data = remake;
		prebuffer = postbuffer = 0;
	}

	template <typename T> void array<T>::clear() {
		size_t adjustment = size >> 1;
		prebuffer += adjustment;
		data += adjustment;
		postbuffer += adjustment;
		postbuffer += size & 1;
		size = 0;
	}

}
#endif
