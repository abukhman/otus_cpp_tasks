#include <string>
#include <vector>
#include <tuple>
#include <type_traits>
#include <iostream>
#include <list>
#include "print_tuple.h"

template<typename T>
auto ip3(T x, int y) -> decltype(x.c_str()) {
  std::cout << x << std::endl;
}

template<typename T>
void ip3(T x, long y) {
  auto it = x.begin();
  if (it != x.end()) {
    std::cout << *it++;
  }
  for (; it != x.end(); it++) {
    std::cout << "." << *it;
  }
  std::cout<<std::endl;
}

template<typename T>
auto ip2(T x) -> decltype(x.begin()) {
  ip3(x, 0);
}

template<typename T>
auto ip2(T x) -> decltype(std::tuple_size<T>{}) {
  print_tuple<T>(x);
}

template<typename T>
void print_ip(T x, std::enable_if_t<!std::is_integral<T>::value, int> y = 0) {
  ip2(x);
}

template<typename T>
void print_ip(T x, std::enable_if_t<std::is_integral<T>::value, int> y = 0) {
  auto pnt = reinterpret_cast<unsigned char *>(&x);
  std::cout << (unsigned) pnt[ (int) sizeof(x) - 1];
  for(int i = (int) sizeof(x) - 2; i >= 0; i--) {
    std::cout << "." << (unsigned) pnt[i];
  }
  std::cout << std::endl;
}


int main()
{
  print_ip( int8_t{-1} ); // 255
  print_ip( int16_t{0} ); // 0.0
  print_ip( int32_t{2130706433} ); // 127.0.0.1
  print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
  print_ip( std::string{"Hello, World!"} ); // Hello, World!
  print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
  print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
  print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
}
