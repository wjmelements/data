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
		T& operator[](const int index); // O(1)
		T get(const int index); // O(1)
		void push_back(const T& elem); // amoritized O(1)
		void push_front(const T& elem); // amoritized O(1)
		T pop_back(); // O(1)
		T pop_front(); // O(1)
		void insert(const int index, const T& elem); // O(n)
		size_t count(); // O(1)
		void reverse(); // O(1)
	};

	template <typename T> void array<T>::tripleSize() {
		prebuffer = postbuffer = (prebuffer + postbuffer + size);
		T* remake = new T[3*prebuffer];
		remake += prebuffer;
		// copy the old material into the new storage
		for(size_t i = 0; i < size; ++i) {
			remake[i] = data[i];
		}
		delete[]data; // might still be a memory leak
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

	template <typename T> void array<T>::insert(const int index, const T& elem) {
		//
	}

	template <typename T> size_t array<T>::count() {
		return size;
	}

	template <typename T> void reverse() {
		//
	}
}
