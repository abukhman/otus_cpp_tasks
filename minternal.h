#ifndef _MATRIX_INTERNAL_H_
#define _MATRIX_INTERNAL_H_

#include <iostream>
#include <map>
#include <cassert>

using namespace std;

template<typename T>
class MatrixInternal {
  map<size_t, map<size_t, T>> data;
 public:

  class iterator {
    typename map<size_t, map<size_t, T>>::iterator pnt1;
    typename map<size_t, T>::iterator pnt2;
    typename map<size_t, map<size_t, T>>::iterator pnt1end;
   public:
    friend bool operator==(const iterator& lhs, const iterator& rhs) {
      if (lhs.pnt1 == rhs.pnt1 && lhs.pnt1 == lhs.pnt1end) return true;
      if (lhs.pnt1 == rhs.pnt1 && lhs.pnt2 == rhs.pnt2) {
        return true;
      }
      return false;
    }

    friend bool operator!=(const iterator& lhs, const iterator& rhs) {
      return !(lhs == rhs);
    }

    iterator(const iterator& it) {
      pnt1 = it.pnt1;
      pnt2 = it.pnt2;
      pnt1end = it.pnt1end;
    }

    iterator& operator++() {
      this->pnt2++;
      if (this->pnt2 == this->pnt1->second.end()) {
        pnt1++;
        pnt2 = pnt1->second.begin();
      }
      return *this;
    }

    iterator(decltype(pnt1) p1, decltype(pnt2) p2, decltype(pnt1end) p1e) {
      pnt1 = p1;
      pnt2 = p2;
      pnt1end = p1e;
    }

    iterator(decltype(pnt1) p1, decltype(pnt1end) p1e) {
      pnt1 = p1;
      pnt1end = p1e;
    }

    tuple<size_t, size_t, T> operator*() {
      return make_tuple(pnt1->first, pnt2->first, pnt2->second);
    }
  };
  iterator begin() {
    if (data.begin() == data.end()) {
      return iterator(data.begin(), data.end());
    }
    return iterator(data.begin(), data.begin()->second.begin(), data.end());
  }
  iterator end() {
    return iterator(data.end(), data.end());
  }
  int getElement(size_t x, size_t y) {
    return data[x][y];
  }

  void set_value(int value, size_t x, size_t y) {
    data[x][y] = value;
    
  }

  void remove_if_exist(size_t x, size_t y) {
    auto xx = data.find(x);
    if (xx == data.end()) {
      return;
    }

    if (data[x].find(y) == data[x].end()) {
      return;
    }

    data[x].erase(y);
    if (data[x].empty()) {
      data.erase(x);
    }
  }

  bool isIn (size_t x, size_t y) {
    auto xx = data.find(x);
    if (xx != data.end()) {
      if (data[x].find(y) != data[x].end()) return true;
    }
    return false;
  }
  size_t size() {
    size_t len = 0;
    for(auto c: data) {
      len += c.second.size();
    }
    return len;
  }
};

#endif
