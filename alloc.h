template <class T>
struct my_allocator {
    static const size_t kb = 100;
    void * base;
    void * buf;
    int pos;
    size_t cur_size = 0;
    using value_type = T;
    my_allocator () noexcept {
	    base = buf = malloc(kb * 1024);
	    pos = 0;
	    if (buf == nullptr) {
              cur_size = 0;
	      return;
	    }
	    cur_size = kb;
    }
    T* allocate (std::size_t n)
    {
	    if (cur_size < n) {
		   throw(std::bad_alloc{});
	    }
	    std::cout<<"allocate "<<n<<" "<<sizeof(T)<<" "<<buf<<std::endl;
	    void* ret_adr = static_cast<T*>(buf);
	    buf = static_cast<void *> (static_cast<T*>(buf) + n);
	    cur_size -= n;
	    return static_cast<T*>(ret_adr);
    }
    void deallocate (T* p, std::size_t n)
    {
	    std::cout<<"deallocate "<<n<<std::endl;
    }
    ~my_allocator() noexcept {
      if (base != nullptr) {
        free(base);
      }
    }
};

