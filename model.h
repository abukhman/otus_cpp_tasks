#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include "elem.h"
#include <vector>
#include <memory>

class Model {
  std::vector<std::unique_ptr<Element>> elements;
 public:
  void load(const std::string& ) {
  }
  void save(const std::string& filename) {
    std::cout<<"Save every element"<<std::endl;
    std::cout<<"Open "<<filename<<std::endl;
    for(int i = 0; i < elements.size(); i++) {
      elements[i]->save();
    }
  }
  decltype(elements)& getFig() {
    return elements;
  }
};

#endif
