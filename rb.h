namespace data {
	template <typename T> class rbtreenode;

	template <typename T> class rbset {
	private:
		rbtreenode<T>* root;
	public:
		rbset();
		size_t size();
		bool empty();
		void clear();
		void add(T elem);
		void remove(T elem);
		bool contains(T elem);
	}

	template <typename K, typename V> class rbmap {
	private:
		struct tuple {
			K key;
			V value;
			bool operator== (tuple& other);
			bool operator< (tuple& other);
		};
		rbtreenode<T>* root;
	public:	
		rbmap();
		size_t size();
		bool empty();
		void clear();
		
	}
}
