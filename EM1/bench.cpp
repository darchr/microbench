#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP   128
#define ITERS 1000000

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t1 = 1 +zero;

  int i;
  for(i=zero; i < ITERS ; i+=1) {
    t1*=t1;
  }
  return t1;
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

