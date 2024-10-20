#include <map>
#include <string>
#include <mutex>
#include <sstream>

class DBServer {
 private:
  std::map<int,  std::string> tableA;
  std::map<int,  std::string> tableB;
  std::mutex m_A;
  std::mutex m_B;
 public:
  std::string parse_command(std::string& s) {
    std::string tmp, result;
    std::istringstream iss(s);
    iss >> tmp;
    if (tmp=="INSERT") {
      iss >> tmp;
      if (tmp=="A") {
        std::lock_guard<std::mutex> lock(m_A);
	int id;
	iss >> id; // обработать ошибку вставки
	iss >> tmp;
	if (tableA.find(id) == tableA.end()) {
          tableA[id] = tmp;
	  result = "OK\n";
	} else {
	  result = "ERR duplicate key\n";
	}
      } else if (tmp=="B") {
        std::lock_guard<std::mutex> lock(m_B);
	int id;
	iss >> id; // обработать ошибку вставки
	iss >> tmp;
	if (tableB.find(id) == tableB.end()) {
          tableB[id] = tmp;
	  result = "OK\n";
	} else {
	  result = "ERR duplicate key\n";
	}
      } else {
	result = "ERR Unknown table name\n";
      }

    } else if (tmp=="TRUNCATE") {
      iss >> tmp;
      if (tmp=="A") {
	std::lock_guard<std::mutex> lock(m_A);
        tableA.clear();
	result = "OK\n";
      } else if (tmp=="B"){
	std::lock_guard<std::mutex> lock(m_B);
        tableB.clear();
	result = "OK\n";
      } else {
        result = "ERR wrong table name\n";
      }
    } else if (tmp=="INTERSECTION") {
      std::lock_guard<std::mutex> lock1(m_A);
      std::lock_guard<std::mutex> lock2(m_B);
      for (const auto& pairA : tableA) {
        if (tableB.find(pairA.first) != tableB.end()) {
          result += std::to_string(pairA.first) + ","
		  + tableA[pairA.first]+","
		  +tableB[pairA.first]+"\n";
	}
      }
      result += "OK\n";
    } else if (tmp=="SYMMETRIC_DIFFERENCE") {
      std::lock_guard<std::mutex> lock1(m_A);
      std::lock_guard<std::mutex> lock2(m_B);
      for (const auto& pairA : tableA) {
        if (tableB.find(pairA.first) == tableB.end()) {
          result += std::to_string(pairA.first) + ","
		  + tableA[pairA.first]+","+"\n";
	}
      }
      for (const auto& pairB : tableB) {
        if (tableA.find(pairB.first) == tableA.end()) {
          result += std::to_string(pairB.first) + ","
		  + ","+tableB[pairB.first]+"\n";
	}
      }
      result += "OK\n";
    } else {
      result = "ERR unknown command\n";
    }
    return result;
  }
};
