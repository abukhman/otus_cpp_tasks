#include <iostream>
#include <string>
#include "store.h"


int main (int argc, const char *argv[]) {
  if (argc != 2) {
    std::cout<<"Usage: "<<argv[0]<<" N"<<std::endl;
    std::cout<<"  N - buffer capacity."<<std::endl;
    return -1;
  }
  int N;
  try {
    N = std::stoi(std::string(argv[1]));
  }
  catch (std::invalid_argument const& ex) {
    std::cout << "std::invalid_argument::what(): " << ex.what() << std::endl;
    return -1;
  }
  catch (std::out_of_range const& ex) {
    std::cout << "std::out_of_range::what(): " << ex.what() << std::endl;
    return -1;
  }
  if (N <= 0) {
	  std::cout<<"N should be positive integer"<<std::endl;
    return -1;
  }

  std::string input_line;
  Store s(N);

  while(std::cin>>input_line) {
    if (input_line == "{") {
      s.open_block();
    } else if (input_line == "}"){
      s.close_block();
    } else {
      s.add(input_line);
    }
  }
}
