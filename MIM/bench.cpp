#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 65536
#define STEP   128
#define ITERS   32

int arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=zero; iter < ITERS; ++iter) {
    for(i=iter; i < ASIZE; i+=1024) {
      t += arr[i+0];
      t += arr[i+1*128];
      t += arr[i+2*128];
      t += arr[i+3*128];
      t += arr[i+4*128];
      t += arr[i+5*128];
      t += arr[i+6*128];
      t += arr[i+7*128];
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
