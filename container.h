#include <list>
#include <memory>
#include <cstring>
#include <iostream>

template<class T, class Allocator = std::allocator<T> >
class my_container {
  std::list<T*> internal;
  Allocator alloc;
public:
  void add(const T& elem) {
    T* new_elem = alloc.allocate(sizeof(T));
    internal.push_back(new_elem);
    memcpy((void *)new_elem, (void *)elem, sizeof(elem));
  }
  void add(const T&& elem) {
    T* new_elem = alloc.allocate(sizeof(T));
    internal.push_back(new_elem);
    T tmp = elem;
    memcpy((void*)new_elem, (void*)&tmp, sizeof(elem));
  }
};
