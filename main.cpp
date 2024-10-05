#include <iostream>
#include <string>

#include "async.h"

using namespace std;

unsigned connect(unsigned bs);
int receive(unsigned ctx, const char *msg);
void disconnect(unsigned ctx_id);
void finilize_async();

int main()
{
  //async_init();
  std::string s;
  auto id = connect(3);
  while(cin>>s) {
    receive(id, s.c_str());
  }
  disconnect(id);
  finilize_async();
}
