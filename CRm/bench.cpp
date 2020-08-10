#include <stdio.h>
#include <string>
#include "randArr.h"
#include "common.h"
#include "cpucounters.h"
#include "filewriting.h"

#define ASIZE 4096

int temp[ASIZE];

void merge(int numbers[], int temp[], int left, int mid, int right)
{
  int i, left_end, num_elements, tmp_pos;
 
  left_end = mid - 1;
  tmp_pos = left;
  num_elements = right - left + 1;
 
  while ((left <= left_end) && (mid <= right))
  {
    if (numbers[left] <= numbers[mid])
    {
      temp[tmp_pos] = numbers[left];
      tmp_pos = tmp_pos + 1;
      left = left +1;
    }
    else
    {
      temp[tmp_pos] = numbers[mid];
      tmp_pos = tmp_pos + 1;
      mid = mid + 1;
    }
  }
 
  while (left <= left_end)
  {
    temp[tmp_pos] = numbers[left];
    left = left + 1;
    tmp_pos = tmp_pos + 1;
  }
  while (mid <= right)
  {
    temp[tmp_pos] = numbers[mid];
    mid = mid + 1;
    tmp_pos = tmp_pos + 1;
  }
 
  for (i=0; i <= num_elements; i++)
  {
    numbers[right] = temp[right];
    right = right - 1;
  }
}


void m_sort(int numbers[], int temp[], int left, int right)
{
  int mid;
 
  if (right > left)
  {
    mid = (right + left) / 2;
    m_sort(numbers, temp, left, mid);
    m_sort(numbers, temp, mid+1, right);
 
    merge(numbers, temp, left, mid+1, right);
  }
}


__attribute__ ((noinline))
void mergeSort(int numbers[], int temp[], int array_size)
{
  m_sort(numbers, temp, 0, array_size - 1);
}
  

int main(int argc, char* argv[]) {
  using namespace std;

  string stat_1_name, stat_2_name;
  float ipc;
  argc&=10000;

  PCM::CustomCoreEventDescription MyEvents[2];

  // Mispredicted Total

  MyEvents[0].event_number = 0xC5; 

  MyEvents[0].umask_value = 0x00;

  // Total Branches number  :

  MyEvents[1].event_number = 0xC4; 

  MyEvents[1].umask_value = 0x00; 

  uint32 core =0;

  if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 1;

  CoreCounterState before_sstate = getCoreCounterState(core);
  mergeSort(randArr,temp,ASIZE);
  CoreCounterState after_sstate = getCoreCounterState(core);

  ipc = getIPC(before_sstate,after_sstate);
  uint64 BRANCH_MISSES_TOTAL_events = getNumberOfCustomEvents(0,before_sstate, after_sstate );
  uint64  BRANCH_TOTAL_INSTR_RETIRED_events = getNumberOfCustomEvents(1,before_sstate,after_sstate );

  stat_1_name = "BRANCH_MISSES_TOTAL_events";
  stat_2_name = "BRANCH_TOTAL_INSTR_RETIRED_events";

  Write_to_file(ipc,stat_1_name,BRANCH_MISSES_TOTAL_events,stat_2_name,BRANCH_TOTAL_INSTR_RETIRED_events);

  volatile int a = temp[argc];
}
