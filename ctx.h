#ifndef __CTX_H__
#define __CTX_H__

#include <queue>
#include <string>
#include <mutex>

using namespace std;
// Store context
struct ctx {
  queue<string> q;
  unsigned block_size;
  int level;
  int64_t time;
  ctx(unsigned bs):level(0), block_size(bs) {
  }
};

#endif // __CTX_H__
