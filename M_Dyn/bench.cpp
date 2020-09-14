#include <stdio.h>
#include <stdlib.h>     /* malloc, free, rand */
#include "monitor.hpp"

#define AMULT 65536
#define ASIZE    32
#define STEP    0
#define AMASK (ASIZE-1)
#define ITERS  65536


int arr1[ASIZE*AMULT];
int arr2[ASIZE*AMULT];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int acc1 = 1, count=0;
  int acc2 = 2;

  unsigned lfsr = 0xACE1u;
  unsigned lfsr2 = 0x0143u;

  do
  {
      /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
      lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xB400u);
      acc1 += arr1[(lfsr&AMASK)*AMULT];

      //printf("write %d, ",lfsr&AMASK);

      lfsr2 = (lfsr2 >> 1) ^ (-(lfsr2 & 1u) & 0xB400u);
      acc2+=1;
      arr1[(lfsr2&AMASK)*AMULT]=acc2;

      //printf("read %d\n",lfsr&AMASK);
  } while(++count < ITERS);
  //} while(lfsr != 0xACE1u);

  return acc1;
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



