#include <stdio.h>
#include <stdlib.h>     /* malloc, free, rand */
#include "monitor.hpp"

#define ASIZE 65536
#define STEP    128
#define ITERS  4096
#define LEN    2048


typedef struct dude {
  int p1,p2,p3,p4;
} dude;


dude arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int count=0;

  unsigned lfsr = 0xACE1u;
  do
  {
      /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
      lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xB400u);
      arr[lfsr].p1 = lfsr;
  } while(++count < ITERS);
  //} while(lfsr != 0xACE1u);

  return arr[zero].p1;
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


