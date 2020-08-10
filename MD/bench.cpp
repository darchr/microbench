#include <stdio.h>
#include <stdlib.h>     /* malloc, free, rand */
#include "cpucounters.h"
#include "filewriting.h"
#include "common.h"

#define ASIZE 2048
#define STEP   128
#define ITERS    4
#define LEN   2048

int arr[ASIZE];

struct ll {
  int val;
  struct ll* _next;
};

__attribute__ ((noinline))
int loop(int zero,struct ll* n) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS; ++iter) {
    struct ll* cur =n;
    while(cur!=NULL) {
      t+=cur->val;
      cur=cur->_next;
    }
  }
  return t;
}

int main(int argc, char* argv[]) {
  using namespace std;

  argc&=10000;

  struct ll *n, *cur;
  int i;
  n=(struct ll* )malloc(sizeof(struct ll));
  cur=n;
  for(i=0;i<LEN;++i) {
    cur->val=i;
    cur->_next=(struct ll* )malloc(sizeof(struct ll));
    cur=cur->_next;
  }
  cur->val=100;
  cur->_next=NULL;

  float ipc;
  uint32 core = 0;
  PCM * m = PCM::getInstance();

  if (m->program() != PCM::Success) return 1;

  CoreCounterState before_sstate = getCoreCounterState(core);
  int t=loop(argc,n);
  CoreCounterState after_sstate = getCoreCounterState(core);

  uint64 l1d_load_hits = getNumberOfCustomEvents(0,before_sstate, after_sstate);
  uint64 total_stores = getNumberOfCustomEvents(1,before_sstate,after_sstate);
  uint64 l1d_replacements = getNumberOfCustomEvents(2,before_sstate,after_sstate);

  cout << "MEM_LOAD_RETIRED_L1_HITS: " << l1d_load_hits << endl;
  cout << "MEM_LOAD_RETIRED_ALL_LOADS: " << total_stores << endl;
  cout << "L1_CACHE_REPLACEMENTS: " << l1d_replacements << endl;

  volatile int a = t;
}
