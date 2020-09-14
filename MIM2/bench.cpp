#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 65536
#define STEP   128
#define ITERS  256

int arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=zero; iter < ITERS; ++iter) {
    for(i=iter; i < ASIZE; i+=1024) {
      t += arr[i+0*128];
      t += arr[i+1*128];
      t += arr[i+2*128];
      t += arr[i+3*128];
      t += arr[i+4*128];
      t += arr[i+4*128+1];
      t += arr[i+6*128];
      t += arr[i+6*128+1];
    }
  }
  return t;
}

int main(int argc, char* argv[]) {

  argc&=10000;
  benchmarkParams(ASIZE, STEP, ITERS);
  switch (*argv[1]) {
    case '0': benchmarkParams(ASIZE, STEP, ITERS); break;
    case '1': getGeneralStats(loop, argc);break;
    case '2': getBranchStats1(loop, argc);break;
    case '3': getBranchStats2(loop, argc);break;
    case '4': getMemStats1(loop, argc);break;
    case '5': getMemStats2(loop, argc);break;
    case '6': getMemStats3(loop, argc);break;
    case '7': getMemStats4(loop, argc);break;
    default: getGeneralStats(loop, argc);
  }
  return 0;
}

