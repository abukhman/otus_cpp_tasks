#include <queue>
#include <string>
#include <mutex>

using namespace std;

struct ctx {
  queue<string> q;
  unsigned block_size;
  int level;
  int64_t time;
  //std::mutex mtx;
  //ctx() {}
  ctx(unsigned bs):level(0), block_size(bs) {
  }
  //ctx& operator=(const ctx&) {
  //  this
  //}
};


