#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "mproxy.h"

template <typename T, T DEF_VAL>
class Matrix {
  MatrixProxy<T,DEF_VAL> _m;
  struct Row {
    size_t num;
    MatrixProxy<T, DEF_VAL>& _m;
    Row(size_t inp, MatrixProxy<T,DEF_VAL>& m): num(inp), _m(m) {
    }
    int& operator[](int y) {
      return _m.getElement(num, y);
    }
    size_t size() {
      return _m.size();
    }
  };
 public:
  Row operator[](int x){
    return Row(x, _m); 
  }

  size_t size() {
    return _m.size();
  }


  class iterator {
    decltype(_m.begin()) _it;
   public:
    iterator(decltype (_it) _it): _it(_it) {}
    tuple<size_t, size_t, T> operator*() {
      return *_it;
    }
    iterator& operator++() {
      ++_it;
      return *this;
    }
    friend bool operator==(const iterator& lhs, const iterator& rhs) {
      return lhs._it == rhs._it;
    }
    friend bool operator!=(const iterator& lhs, const iterator& rhs) {
      return lhs._it != rhs._it;
    }
  };

  iterator begin() {
    return iterator(_m.begin());
  }

  iterator end() {
    return iterator(_m.end());
  }

};

#endif
