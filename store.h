#ifndef _STORE_H_
#define _STORE_H_
#include "complex_loger.h"

class Store {
  queue<std::string> buffer;
  size_t N;
  unsigned level;

  ComplexLoger _l;
  
 public:
  Store(size_t N): N(N), level(0), _l() {}
  void add(const std::string& name) {
    buffer.push(name);
    if (level == 0 && buffer.size() == N) {
      flush();
    }
  }

  void open_block() {
    if (level == 0) {
      flush();
    }
    level++;
  }

  void close_block() {
    level--;
    if (level == 0) {
      flush();
    }
  }

  void flush() {
    if (buffer.empty() || (level > 0)) return;
    _l<<"bulk: "<<buffer.front();
    buffer.pop();
    while (!buffer.empty()) {
      _l<<", "<<buffer.front();
      buffer.pop();
    }
    _l.flush();
  }

  ~Store() {
    flush();
  }
};

#endif
