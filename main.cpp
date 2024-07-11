#include <iostream>
#include "alloc.h"
#include "container.h"
#include <map>

using namespace std;

template<class T>
void fill_map(T& arg) {
    int fact = 1;
    for (auto i = 0; i < 10; i++) {
      fact *= i == 0 ? 1 : i;
      arg[i] = fact;
    }	
}

template<class T>
void print_map(T& arg) {
    for (auto it = arg.begin(); it != arg.end(); it++) {
      cout<<it->first<<" "<<it->second<<endl;
    }
}

int main (int, char **) {
    std::map<int, int> map1;
    fill_map(map1);

    std::map<int, int, std::less<int>, my_allocator<std::pair<int, int>>> map2;
    fill_map(map2);
    print_map(map2);

    my_container<int> M;
    M.add(1);
    M.add(2);

    return 0;
}
