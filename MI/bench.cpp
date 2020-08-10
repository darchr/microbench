#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP   128
#define ITERS   32

int arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS; ++iter) {
    for(i=zero; i < 2048; i+=8) {
      t += arr[i+0];
      t += arr[i+1];
      t += arr[i+2];
      t += arr[i+3];
      t += arr[i+4];
      t += arr[i+5];
      t += arr[i+6];
      t += arr[i+7];
      t += i; //cause the paper said so!
    }
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
