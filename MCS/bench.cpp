#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 8192
#define STEP   512
#define ITERS   0

float arr[ASIZE];
float arr1[ASIZE];
float arr2[ASIZE];
float arr3[ASIZE];
float arr4[ASIZE];
float arr5[ASIZE];
float arr6[ASIZE];
float arr7[ASIZE];
float arr8[ASIZE];
float arr9[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  float f = 0;
  for(int i = 0; i < ASIZE; i+=1) {
    int ind=i&(STEP-1);
    arr1[ind]=i;
    arr2[ind]=i;
    arr3[ind]=i;
    arr4[ind]=i;
    arr5[ind]=i;
    arr6[ind]=i;
    arr7[ind]=i;
    arr8[ind]=i;
    arr9[ind]=i;
    //f=f*f*f*f*f*f*f*f*f*f*f;
  }
  return f;
}

int main(int argc, char* argv[]) {

  argc&=10000;
  benchmarkParams(ASIZE, STEP, ITERS);
  switch (*argv[1]) {
    case '0': getGeneralStats(loop, argc);break;
    case '1': getBranchStats1(loop, argc);break;
    case '2': getBranchStats2(loop, argc);break;
    case '3': getMemStats1(loop, argc);break;
    case '4': getMemStats2(loop, argc);break;
    case '5': getMemStats3(loop, argc);break;
    case '6': getMemStats4(loop, argc);break;
    default: getGeneralStats(loop, argc);
  }
  return 0;
}
