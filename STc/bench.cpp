#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP  1024
#define ITERS   16

int arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=zero; iter < ITERS; ++iter) {
    for(i=zero; i < STEP; ++i) {
      arr[i]=i;
    }
    t+=arr[ASIZE-1-zero];
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
