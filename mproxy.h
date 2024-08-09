#ifndef _M_PROXY_H_
#define _M_PROXY_H_
#include <iostream>
#include <map>
#include <cassert>

#include "minternal.h"

using namespace std;

template<typename T, T DEF_VAL>
class MatrixProxy {
  MatrixInternal<T> _m;
  T tmp;
  size_t idx;
  size_t idy;
  bool enabled;

  void flush() {
    if (tmp == DEF_VAL) {
      _m.remove_if_exist(idx, idy);
      return;
    } else {
      _m.set_value(tmp, idx, idy);
    }
  }
 public:
  class iterator {
    typename MatrixInternal<T>::iterator _it;
   public:
    tuple<size_t, size_t, T> operator*() {
      return *_it;
    }
    iterator& operator++() {
      ++_it;
      return *this;
    }
    friend bool operator==(const iterator& lhs, const iterator& rhs) {
      if (lhs._it == rhs._it) return true;
      return false;
    }
    friend bool operator!=(const iterator& lhs, const iterator& rhs) {
      if (lhs._it != rhs._it) return true;
      return false;
    }
    iterator(const decltype(_it) & iter):_it(iter) {
      //_it = iter;
    } 
  };

  iterator begin() {
    flush();
    return iterator(_m.begin());
  }

  iterator end() {
    return iterator(_m.end());
  }

  MatrixProxy():_m(), tmp(DEF_VAL), idx(0), idy(0) {}
  int& getElement(size_t x, size_t y) {
    if (tmp == DEF_VAL) {
      _m.remove_if_exist(idx, idy);
    }

    if (tmp != DEF_VAL) {
      _m.set_value(tmp, idx, idy);
    }

    idx = x;
    idy = y;
    tmp = DEF_VAL;
    if (_m.isIn(x, y)) {
      tmp = _m.getElement(x, y);
    }
    return tmp;
  }
  size_t size() {
    if (_m.isIn(idx, idy) && (tmp==DEF_VAL)) {
      return _m.size() - 1;
    }
    if (!_m.isIn(idx, idy) && (tmp!=DEF_VAL)) {
      return _m.size() + 1;
    }
    return _m.size();
  }
};

#endif
