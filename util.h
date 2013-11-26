#ifndef util_w
#define util_w

#include<cstdlib>
#include<cstddef>
#include "beap.h"

namespace data {
	// Conveniences
	template <typename T> T max(T one, T two); // O(1)
	template <typename T> T min(T one, T two); // O(1)
	void rseed(size_t seed); // O(1)
	template <typename T> T randomData(); // O(sizeof(T))
    template <typename K, typename V> V** map(K** input, size_t nmemb, V* (*func)(K*));
	// Sorts
	template <typename T> T* quicksort(T* start, size_t size); // O(n^2)
	template <typename T> T* mergesort(T* start, size_t size); // O(n log n)
	template <typename T> T* radixsort(T* start, size_t size); // O(sizeof(T) n)
	template <typename T> T* triesort(T* start, size_t size); // O(sizeof(T) n)
	template <typename T> T* heapsort(T* start, size_t size); // O(n log n)
	// Shuffles
	template <typename T> T* heapshuffle(T* start, size_t size); // O(n log n)
	template <typename T> T* mergeshuffle(T* start, size_t size); // O(n log n)
	template <typename T> T* quickshuffle(T* start, size_t size); // O(n^2)

	template <typename T> T max(T one, T two) {
		return one > two ? one : two;
	}
	template <typename T> T min(T one, T two) {
		return one < two ? one: two;
	}
	void rseed(size_t seed) {
		srand(seed);
	}
	template <typename T> T randomData() {
		T product;
		char* data = (char*) &product;
		for (size_t i = 0; i < sizeof(T); ++i) {
			data[i] = (char) rand() & 0xFF;
		}
		return product;
	}
	template <> bool randomData() {
		return rand() & 1;
	}

    #define map_do_divides 1
    template <typename K, typename V> struct map_do_param {
        K** input;
        V** output;
        V* (*func)(K*);
        size_t interval;
        size_t remaining; // inclusive
    };
    template <typename K, typename V> void* map_do(void* arg) {
        struct map_do_param<K,V>* param = (struct map_do_param<K,V>*) arg;
        size_t i;
        pthread_t kids[map_do_divides];
        for (i = 0; i < map_do_divides; i++) {
            size_t offset = (i + 1) * param->interval;
            if (offset < param->remaining) {
                struct map_do_param<K,V>* spawn = (struct map_do_param<K,V>*) malloc(sizeof(map_do_param<K,V>));
                spawn->input = param->input + offset;
                spawn->output = param->output + offset;
                spawn->func = param->func;
                spawn->interval = param->interval * map_do_divides;
                spawn->remaining = param->remaining - offset;
                pthread_create(&(kids[i]), NULL, map_do<K,V>, spawn);
            } else {
                break;
            }
        }
        *param->output = param->func(*param->input);
        free(param);
        for (size_t j = 0; j < i; j++) {
            pthread_join(kids[j], NULL);
        }
        return EXIT_SUCCESS;
    }
    template <typename K, typename V> V** map(K** input, size_t nmemb, V* (*func)(K*)) {
        V** ret = (V**) malloc(sizeof(V*) * nmemb);
        struct map_do_param<K,V>* param = (struct map_do_param<K,V>*) malloc(sizeof(map_do_param<K,V>));
        param->input = input;
        param->output = ret;
        param->func = func;
        param->interval = 1;
        param->remaining = nmemb;
        if (nmemb) {
            map_do<K,V>(param);
        }
        return ret;
    }

	template <typename T> T* quicksort(T* start, size_t size) {
		if (size < 2) {
			return start;
		}
		T* larger = new T[size - 1];
		size_t large = 0;
		T* smaller = new T[size - 1];
		size_t small = 0;
		T first = start[0];
		for (size_t i = 1; i < size; ++i) {
			if (start[i] < first) {
				smaller[small++] = start[i];
			}
			else {
				larger[large++] = start[i];
			}
		}
		smaller = quicksort(smaller,small);
		larger = quicksort(larger,large);
		// merge
		size_t index = 0;
		while (index < small) {
			start[index] = smaller[index];
			++index;
		}
		start[index++] = first;
		size_t offset = small + 1;
		while (index < size) {
			start[index] = larger[index - offset];
			++index;
		}
		delete[] smaller;
		delete[] larger;
		return start;
	}

	template <typename T> T* heapsort(T* start, size_t size) {
		beap<T> heap;
		for (size_t i = 0; i < size; ++i) {
			heap.insert(start[i]);
		}
		for (size_t i = 0; i < size; ++i) {
			start[i] = heap.pop();
		}
		return start;
	}

	template <typename T> T* heapshuffle(T* start, size_t size) {
		priorityq<char,T> scramble;
		for (size_t i = 0; i < size; ++i) {
			scramble.insert(randomData<char>(),start[i]);
		}
		for (size_t i = 0; i < size; ++i) {
			start[i] = scramble.pop();
		}
	}

	template <typename T> T* mergeshuffle(T* start, size_t size) {
		if (size < 2) {
			return start;
		}
		T* larger = new T[size - 1];
		size_t large = 0;
		T* smaller = new T[size - 1];
		size_t small = 0;
		T first = start[0];
		for (size_t i = 1; i < size; ++i) {
			if (randomData<bool>()) {
				smaller[small++] = start[i];
			}
			else {
				larger[large++] = start[i];
			}
		}
		smaller = mergeshuffle(smaller,small);
		larger = mergeshuffle(larger,large);
		// merge
		size_t index = 0;
		while (index < small) {
			start[index] = smaller[index];
			++index;
		}
		start[index++] = first;
		size_t offset = small + 1;
		while (index < size) {
			start[index] = larger[index - offset];
			++index;
		}
		delete[] smaller;
		delete[] larger;
		return start;

	}
}
#endif
