#include <stdio.h>
#include <stdlib.h>     /* malloc, free, rand */
#include "monitor.hpp"

#define ASIZE  65536
#define STEP     128
#define ITERS  65536
#define LEN     2048


typedef struct dude {
  int p1,p2,p3,p4;
} dude;


dude arr[ASIZE];
template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0, count=0;

  unsigned lfsr = 0xACE1u;
  do
  {
      count++;
      /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
      lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xB400u);

      arr[lfsr].p4=lfsr + arr[lfsr].p1 + arr[lfsr].p2 + arr[lfsr].p3;

      //lfsr = lfsr + arr[lfsr].p1;

  } while(++count < ITERS);
  //} while(lfsr != 0xACE1u);

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

