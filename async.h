#ifndef __ASYNC_H_
#define __ASYNC_H_

unsigned connect(unsigned bs);
void receive(unsigned ctx, const char *msg);
void disconnect(unsigned ctx_id);
void finilize_async();

#endif // __ASYNC_H_
