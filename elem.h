#ifndef _ELEM_H_
#define _ELEM_H_

#include <iostream>

enum elem_id {
  POINT, LINE, CIRCLE
};


class Element {
  int id;
 public:
  virtual void save()=0;
  virtual void show()=0;

};

class Point: public Element {
  int x;
  int y;
public:
  void save() {
    std::cout<<"Save point"<<std::endl;
  }
  void show() {
    std::cout<<"Show point"<<std::endl;
  }
};

class Line: public Element {
  int x1, y1;
  int x2, y2;
public:
  void save() {
    std::cout<<"Save line"<<std::endl;
  }
  void show() {
    std::cout<<"Show point"<<std::endl;
  }

};

class Circle: public Element {
public:
  void save() {
    std::cout<<"Save circle"<<std::endl;
  }
  void show() {
    std::cout<<"Show point"<<std::endl;
  }

};
#endif
