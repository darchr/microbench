#include <stdio.h>
#include "randArr.h"
#include "monitor.hpp"

#define ASIZE 16384
#define STEP  16384
#define ITERS    32

int arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS; ++iter) {
    for(i=0; i < STEP + zero; i+=1) {
      if(randArr[i])  {
        t+=3+3*t;
        arr[i]=t;
      } else {
        t-=1-5*t;
      }
    }
  }
  return arr[zero]+t;
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
