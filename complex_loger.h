#ifndef _COMPLEX_LOGER_H_
#define _COMPLEX_LOGER_H_

#include "loger.h"

class ComplexLoger: public Loger {
  FileSaver _lf;
  Printer _lc;
 public:
  ComplexLoger& operator<<(const std::string& s) {
    _lf<<s;
    _lc<<s;
    return *this;
  }

  void flush() {
    _lf.flush();
    _lc.flush();
  }
};
#endif
