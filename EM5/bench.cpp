#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP   128
#define ITERS 1000000

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t1 = 1 +zero;
  int t2 = 89+zero;
  int t3 = 3 +zero;
  int t4 = 21+zero;
  int t5 = 2 +zero;

  int i;

  for(i=zero; i < ITERS; i+=1) {
    t1*=t2;
    t2*=t3;
    t3*=t4;
    t4*=t5;
    t5*=t1;
  }
  return t1+t2+t3+t4+t5;
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
