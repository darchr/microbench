#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP   128
#define ITERS 1000000

template <typename type>
__attribute__((optimize("no-unroll-loops")))
type loop(int zero) {
  float  t1 = 1.1f;
  float  t2 = 89.0f;
  float  t3 = 3.2f;
  float  t4 = 21.0f;
  float  t5 = 2.0f;
  float  t6 = 7.0f;
  float  t7 = 2.5f;
  float  t8 = 3.0f;

  int i;
  for(i=0; i < ITERS; i+=1) {
    t1*=0.2f;
    t2*=0.4f;
    t3*=1.2f;
    t4*= 0.12f;
    t5*= 0.13f;
    t6*= 0.14f;
    t7*= 0.15f;
    t8*= 0.16f;
  }
  return t1+t2+t3+t4+t5+t6+t7+t8;
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

