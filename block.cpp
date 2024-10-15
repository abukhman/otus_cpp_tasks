#include "block.h"

std::atomic<int> Block::cnt(0);

void Block::add(std::string_view s) {
    if (m_store.empty()) {
      auto now = std::chrono::system_clock::now();
      ts = std::chrono::system_clock::to_time_t(now);
    }
    std::string tmp({s.begin(), s.end() - 1});
    if (tmp == "{") {
	if (!m_store.empty()) {
	  std::stringstream fn;
	  fn << "bulk_" << ts << "_" << cnt++;
	  std::ofstream ff(fn.str());
	  print(ff);
          print(std::cout);
          m_store.clear();
	}
        level++;
    } else if (tmp == "}") {
        level--;
        if (level == 0) {
	  std::stringstream fn;
	  fn << "bulk_" << ts << "_" << cnt++;
	  std::ofstream ff(fn.str());
	  print(ff);
          print(std::cout);
          m_store.clear();
	}
    } else {
      m_store.push_back(tmp);
      if (level == 0 && m_store.size() >= m_size) {
	std::stringstream fn;
	fn << "bulk_" << ts << "_" << cnt++;
	std::ofstream ff(fn.str());
	print(ff);
        print(std::cout);
        m_store.clear();
      }
    }
}

void Block::print(std::ostream& ss) {
    if (m_store.empty()) return;
    ss << "bulk: " << *m_store.begin();
    for(auto i = m_store.begin() + 1; i!=m_store.end(); i++) {
      ss << ", " << *i;
    }
    ss << std::endl;
}
