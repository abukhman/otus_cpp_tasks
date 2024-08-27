#ifndef _LOGER_H_
#define _LOGER_H_

#include <iostream>
#include <chrono>
#include <queue>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;

class Loger {
  virtual Loger& operator<<(const std::string&) = 0;
};

class Printer: public Loger {
 public:
  Printer& operator<<(const std::string& s) {
    cout<<s;
    return *this;
  }
  void flush() {
    cout<<endl;
  }
};

class FileSaver: public Loger {
  ofstream _File;
 public:
  FileSaver& operator<<(const std::string& s) {
    if (!_File.is_open()) {
      auto now = std::chrono::system_clock::now();
      int tm = std::chrono::system_clock::to_time_t(now);
      std::stringstream _filename;
      _filename << "bulk_" << tm << ".log";
      _File.open(_filename.str());
    }
    _File << s;
    return *this;
  }
  void flush() {
    if (_File.is_open()) {
      _File.close();
    }
  }
  virtual ~FileSaver() {
    flush();
  }
};
#endif
