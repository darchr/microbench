#include <stdio.h>
#include "common.h"

#define ASIZE  2048
#define STEP   128

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
   //loop0(argc);
   //loop1(argc);
   //loop2(argc);

   ROI_BEGIN();
   float f =loop3(argc);
   ROI_END();
   volatile float a = f;

  //  printf("Address of arr1 = %p\n", arr1);
  //  printf("Address of arr2 = %p\n", arr2);
  //  printf("Address of arr3 = %p\n", arr3);
  //  printf("Address of arr4 = %p\n", arr4);
  //  printf("Address of arr5 = %p\n", arr5);
  //  printf("Address of arr6 = %p\n", arr6);
  //  printf("Address of arr7 = %p\n", arr7);
  //  printf("Address of arr8 = %p\n", arr8);
  //  printf("Address of arr9 = %p\n", arr9);
}
