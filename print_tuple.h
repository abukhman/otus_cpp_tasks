#include <tuple>
#include <iostream>

template <class T, int num>
struct TPrnt {
  static void print(T t) {
    TPrnt<T, num - 1>::print(t);
    std::cout << "." << std::get<num>(t);
  }
};

template <class T>
struct TPrnt<T, 0> {
  static void print(T t) {
    std::cout << std::get<0>(t);
  }
};

template <class T>
void print_tuple(T& t) {
  TPrnt<T, std::tuple_size<T>{} - 1>::print(t);
  std::cout<<std::endl;
}

/*int main()
{
  auto tpl = std::make_tuple(1);
  print_tuple(tpl);
  std::cout<<std::endl;
  return 0;
}*/
