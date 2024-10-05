#include <queue>
#include <map>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>

#include "ctx.h"

using namespace std;
// Context manager part
class ContextManager {
  unsigned _n_ctx_id;
  map<int, ctx> contexts;
 public:
  mutex mtx;
  unsigned add_ctx(unsigned bs) {
    _n_ctx_id++;
    contexts.emplace(_n_ctx_id, ctx(bs));
    return _n_ctx_id;
  }
  ctx& operator[](unsigned num) {
    return contexts.find(num)->second;
  }
  void erase(unsigned id) {
    contexts.erase(id);
  }
};

static ContextManager GCM;

// Queue
struct Block {
  queue<string> q;
  uint64_t ts;
  Block(uint64_t t, queue<string> _q):ts(t), q(_q) {}
};

std::queue<Block> messageQueue;
int log_record_id = 0;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;


std::queue<Block> coutQueue;
std::mutex mtx2;
std::condition_variable cv2;

void produce(queue<string> &q, uint64_t t) {
  {
    std::lock_guard<std::mutex> lock(mtx);
    messageQueue.push(Block(t, q));
  }
  cv.notify_one();
  {
    std::lock_guard<std::mutex> lock(mtx2);
    coutQueue.push(Block(t, q));
  }
  cv2.notify_one();
  // clear queue 
  queue<string> empty;
  swap(q, empty);
}


// Functions related to loggers
void FileLogger() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !messageQueue.empty() || finished;});
	if (!messageQueue.empty()) {
          auto message = messageQueue.front();
          messageQueue.pop();
          std::stringstream _filename;
          _filename << "bulk_" << message.ts << "_" << log_record_id++ << ".log";
          ofstream _File(_filename.str());
	  _File << "Commands:";
	  while (!message.q.empty()) {
            _File << " " << message.q.front();
	    message.q.pop();
	  }
	  _File << endl;
	  _File.close();
	}

        if (finished && messageQueue.empty()) break;
    }
}

void TermLogger() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv2.wait(lock, [] { return !coutQueue.empty() || finished;});
	if (!coutQueue.empty()) {
          auto message = coutQueue.front();
          coutQueue.pop();
	  cout << "bulk:";
	  while (!message.q.empty()) {
		  cout << " " << message.q.front();
	    message.q.pop();
	  }
	  cout << endl;
	}

        if (finished && coutQueue.empty()) break;  // Выходим, если производитель закончил
    }
}

thread File1(FileLogger);
thread File2(FileLogger);
thread Term(TermLogger);

// Interface function

void finilize_async() {
  finished = true;
  cv.notify_all();
  cv2.notify_all();
  Term.join();
  File1.join();
  File2.join();
}

unsigned connect(unsigned bs) {
    return GCM.add_ctx(bs);
}

void receive(unsigned ctx, const char *msg) {
  auto& tmp = GCM[ctx];
  {
    std::lock_guard<std::mutex> lock(GCM.mtx);
    if (string(msg) == "{") {
      if (tmp.level == 0 && !tmp.q.empty()) {
        produce(tmp.q, tmp.time);
	tmp.time = 0;
      }
      tmp.level++;
    } else if (string(msg) == "}") {
      tmp.level--;
      if (tmp.level == 0) {
        produce(tmp.q, tmp.time);
	tmp.time = 0;
      }
    } else {
      // handle case with block_size
      tmp.q.push(string(msg));
      auto now = std::chrono::system_clock::now();
      if (tmp.time == 0) tmp.time = std::chrono::system_clock::to_time_t(now); 
      if (tmp.q.size() == GCM[ctx].block_size) {
	produce(tmp.q, tmp.time);
	tmp.time = 0;
      }
    }
  }
}

void disconnect(unsigned ctx_id) {
  auto& tmp = GCM[ctx_id];
  {
    std::lock_guard<std::mutex> lock(GCM.mtx);
    if (!tmp.q.empty()) produce(tmp.q, tmp.time);
  }
  GCM.erase(ctx_id);
}

