#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP   128
#define ITERS   32

__attribute__ ((noinline))
int fib(int i ){
  if(i==0) return 0;
  if(i==1) return 1;
  return fib(i-1) + fib(i-2);
}

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS; ++iter) {
    t+=fib(iter);
  }
  return t;
}

int main(int argc, char* argv[]) {

  argc&=10000;
  benchmarkParams(ASIZE, STEP, ITERS);
  switch (*argv[1]) {
    case '0': getGeneralStats(loop, argc);
              break;
    case '1': getBranchStats1(loop, argc);
              getBranchStats2(loop, argc);
              break;
    case '2': getMemStats1(loop, argc);
              getMemStats2(loop, argc);
              getMemStats3(loop, argc);
              getMemStats4(loop, argc);
              break;
    default: getGeneralStats(loop, argc);
  }
  return 0;
}
