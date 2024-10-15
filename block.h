#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <atomic>
#include <chrono>
#include <sstream>

class Block {
  static std::atomic<int> cnt;
  unsigned m_size = 3;
  std::vector<std::string> m_store;
  uint64_t ts;
  int level;
 public:

  Block(unsigned sz): m_size(sz) {
  }
  Block() {}
void add(std::string_view s);
void print(std::ostream& ss);
};
