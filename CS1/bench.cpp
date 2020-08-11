#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 2048
#define STEP    256
#define ITERS   512

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS+zero; ++iter) {
    for(i=zero; i < STEP; ++i) {
      switch(i) {
        case 0: t+=1; t|=2; break;
        case 1: t+=4; t|=4; break;
        case 2: t-=4; t|=3; break;
        case 3: t+=2; t|=4; break;
        case 4: t-=3; t|=5; break;
        case 5: t+=2; t|=3; break;
        case 6: t-=3; t|=2; break;
        case 7: t-=1; t|=2; break;
        case 8: t-=2; t|=3; break;
        case 9: t-=1; t|=1; break;
      }
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
