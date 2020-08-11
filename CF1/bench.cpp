#include <stdio.h>
#include "randArr.h"
#include "monitor.hpp"

#define ASIZE 2048
#define STEP   128
#define ITERS   64

__attribute__ ((noinline))
int loopy_helper(int i,int zero){
  return (i*2+zero)*3+(i+zero)*(i+zero);
}

__attribute__ ((noinline))
int func_loopy(int i,int zero){
  int l,k=i;
  if(i<16) {
    return loopy_helper(i+4,zero);
  }
  for(l=i-16; l < i+zero; ++l) {
    k+=(k+l+randArr[l])&0x10101;
    randArr[l]=loopy_helper(k,zero);
  }
  return k;
}

__attribute__ ((noinline))
int func_no_loopy(int i ){
  return (i+10+randArr[i])%16;
}

template <typename type>
__attribute__ ((noinline))
type loop(int zero) {
  int t = 0,i,iter;
  for(iter=zero; iter < ITERS; ++iter) {
    //ROI_BEGIN();
    t+=func_loopy(iter,zero);
    //ROI_END();
  }

  //ROI_BEGIN();
  for(iter=zero; iter < ITERS; ++iter) {
    //ROI_BEGIN();
    t+=func_no_loopy(iter);
    //ROI_END();
  }
  //ROI_END();

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