#include <stdio.h>
#include "common.h"

#define ASIZE 8192
#define STEP  512

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

__attribute__ ((noinline))
float loop3(int zero) {
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
  printf("&arr1 = %p\n", arr1);
  printf("&arr2 = %p\n", arr2);
  printf("&arr3 = %p\n", arr3);
  printf("&arr4 = %p\n", arr4);
  printf("&arr5 = %p\n", arr5);
  printf("&arr6 = %p\n", arr6);
  printf("&arr7 = %p\n", arr7);
  printf("&arr8 = %p\n", arr8);
  printf("&arr9 = %p\n", arr9);
  return f;
}

int main(int argc, char* argv[]) {
   argc&=10000;
   ROI_BEGIN();
   float f =loop3(argc);
   ROI_END();
   volatile float a = f;
   return 0;
}
