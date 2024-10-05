#include <iostream>
#include <string>

#include "async.h"

using namespace std;

int main()
{
  std::string s;
  auto id = connect(3);
  while(cin>>s) {
    receive(id, s.c_str());
  }
  disconnect(id);
  finilize_async();
}
