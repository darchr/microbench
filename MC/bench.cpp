#include <stdio.h>
#include "monitor.hpp"

#define ASIZE 8192
#define STEP  128
#define ITERS 0

float arr1[ASIZE];
float arr2[ASIZE];
float arr3[ASIZE];
float arr4[ASIZE];
float arr5[ASIZE];
float arr6[ASIZE];
float arr7[ASIZE];
float arr8[ASIZE];
float arr9[ASIZE];
float arr[ASIZE];

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  float f = 0;
  for(int i = 0; i < ASIZE; i+=1) {
    int ind=i&(STEP-1);
    f+=arr1[ind];
    f+=arr2[ind];
    f+=arr3[ind];
    f+=arr4[ind];
    f+=arr5[ind];
    f+=arr6[ind];
    f+=arr7[ind];
    f+=arr8[ind];
    f+=arr9[ind];
    // f+=arr[ind];
  }
  return f;
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
