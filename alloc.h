template <class T>
struct my_allocator {
    static const size_t kb = 100;
    void * buf;
    int pos;
    size_t cur_size = 0;
    using value_type = T;
    my_allocator () noexcept {
	    buf = malloc(kb * 1024);
	    pos = 0;
	    cur_size = kb;
    }
    T* allocate (std::size_t n)
    {
	    std::cout<<"allocate "<<n<<" "<<sizeof(T)<<" "<<buf<<std::endl;
	    void* ret_adr = static_cast<T*>(buf);
	    buf = static_cast<void *> (static_cast<T*>(buf) + n);
	    return static_cast<T*>(ret_adr);
    }
    void deallocate (T* p, std::size_t n)
    {
	    std::cout<<"deallocate "<<n<<std::endl;
    }
};

