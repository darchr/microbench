#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include <cstdarg>
#include "cpucounters.h"
#include "events.hpp"

using namespace std;

// template <int, float> objType;

void benchmarkParams (int asize, int step, int iters) {
    cout << "ASIZE: " << asize << endl;
    cout << "STEP: " << step << endl;
    cout << "ITERS: " << iters << endl;
}

bool getGeneralStats (float (*func)(int), int n) {
    uint32 core = 0;
    PCM * m = PCM::getInstance();
    if (m->program() != PCM::Success) return 0;
    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    double ipc = getIPC(before_sstate,after_sstate);
    uint64 cycles = getCycles(before_sstate,after_sstate);
    uint64 insts_ret = getInstructionsRetired(before_sstate,after_sstate);

    cout << "ipc: " << ipc << endl;
    cout << "cycles: " << cycles << endl;
    cout << "instructions: " << insts_ret << endl;
    volatile int a = t;
    return 1;
}

bool getBranchStats1 (float (*func)(int), int n) {
    uint32 core = 0;
    PCM::CustomCoreEventDescription MyEvents[3];

    // Load hits in L1D
    MyEvents[0].event_number = EVENT_BR_RETIRED;
    MyEvents[0].umask_value = MASK_BR_RETIRED_ALL;

    // Load misses in L1D
    MyEvents[1].event_number = EVENT_BR_RETIRED;
    MyEvents[1].umask_value = MASK_BR_RETIRED_COND;

    // LFB hits
    MyEvents[2].event_number = EVENT_BR_RETIRED;
    MyEvents[2].umask_value = MASK_BR_RETIRED_NOT_TAKEN;

    if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 0;

    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    uint64 branch_insts = getNumberOfCustomEvents(0,before_sstate, after_sstate);
    uint64 cond_branches = getNumberOfCustomEvents(1,before_sstate,after_sstate);
    uint64 not_taken = getNumberOfCustomEvents(2,before_sstate,after_sstate);

    cout << "branch_insts: " << branch_insts << endl;
    cout << "cond_branches: " << cond_branches << endl;
    cout << "not_taken: " << not_taken << endl;
    volatile int a = t;
    return 1;
}

bool getBranchStats2 (float (*func)(int), int n) {
    uint32 core = 0;
    PCM::CustomCoreEventDescription MyEvents[3];

    // Load hits in L1D
    MyEvents[0].event_number = EVENT_BR_RETIRED_MISP;
    MyEvents[0].umask_value = MASK_BR_RETIRED_ALL;

    // Load misses in L1D
    MyEvents[1].event_number = EVENT_BR_RETIRED_MISP;
    MyEvents[1].umask_value = MASK_BR_RETIRED_COND;

    // LFB hits
    MyEvents[2].event_number = EVENT_BR_RETIRED_MISP;
    MyEvents[2].umask_value = MASK_BR_RETIRED_NEAR_TAKEN;

    if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 0;

    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    uint64 branch_misp = getNumberOfCustomEvents(0,before_sstate, after_sstate);
    uint64 cond_misp = getNumberOfCustomEvents(1,before_sstate,after_sstate);
    uint64 near_taken_misp = getNumberOfCustomEvents(2,before_sstate,after_sstate);

    cout << "branch_misp: " << branch_misp << endl;
    cout << "cond_misp: " << cond_misp << endl;
    cout << "near_taken_misp: " << near_taken_misp << endl;
    volatile int a = t;
    return 1;
}

bool getMemStats1 (float (func(int)), int n) {

    uint32 core = 0;
    PCM::CustomCoreEventDescription MyEvents[3];

    // All L2 requests
    MyEvents[0].event_number = EVENT_MEM_LOADS;
    MyEvents[0].umask_value = MASK_L1_LOAD_HITS;

    // All requests that miss L2 cache
    MyEvents[1].event_number = EVENT_MEM_LOADS;
    MyEvents[1].umask_value = MASK_L2_LOAD_HITS;

    // Demand requests to L2 cache
    MyEvents[2].event_number = EVENT_MEM_LOADS;
    MyEvents[2].umask_value = MASK_L3_LOAD_HITS;

    if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 0;

    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    uint64 l1d_load_hit = getNumberOfCustomEvents(0,before_sstate, after_sstate);
    uint64 l2_load_hit = getNumberOfCustomEvents(1,before_sstate,after_sstate);
    uint64 l3_load_hit = getNumberOfCustomEvents(2,before_sstate,after_sstate);

    cout << "l1d_load_hit: " << l1d_load_hit << endl;
    cout << "l2_load_hit: " << l2_load_hit << endl;
    cout << "l3_load_hit: " << l3_load_hit << endl;
    volatile int a = t;
    return 1;
}

bool getMemStats2 (float (func(int)), int n) {

    uint32 core = 0;
    PCM::CustomCoreEventDescription MyEvents[3];

    // All L2 requests
    MyEvents[0].event_number = EVENT_MEM_LOADS;
    MyEvents[0].umask_value = MASK_L1_LOAD_MISS;

    // All requests that miss L2 cache
    MyEvents[1].event_number = EVENT_MEM_LOADS;
    MyEvents[1].umask_value = MASK_L2_LOAD_MISS;

    // Demand requests to L2 cache
    MyEvents[2].event_number = EVENT_MEM_LOADS;
    MyEvents[2].umask_value = MASK_L3_LOAD_MISS;

    if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 0;

    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    uint64 l1d_load_miss = getNumberOfCustomEvents(0,before_sstate, after_sstate);
    uint64 l2_load_miss = getNumberOfCustomEvents(1,before_sstate,after_sstate);
    uint64 l3_load_miss = getNumberOfCustomEvents(2,before_sstate,after_sstate);

    cout << "l1d_load_miss: " << l1d_load_miss << endl;
    cout << "l2_load_miss: " << l2_load_miss << endl;
    cout << "l3_load_miss: " << l3_load_miss << endl;
    volatile int a = t;
    return 1;
}

bool getMemStats3 (float (func(int)), int n) {

    uint32 core = 0;
    PCM::CustomCoreEventDescription MyEvents[3];

    // All L2 requests
    MyEvents[0].event_number = EVENT_MEM_LOADS;
    MyEvents[0].umask_value = MASK_FB_LOAD_HITS;

    // All requests that miss L2 cache
    MyEvents[1].event_number = EVENT_MEM_INTS_ALL;
    MyEvents[1].umask_value = MASK_ALL_LOADS;

    // Demand requests to L2 cache
    MyEvents[2].event_number = EVENT_MEM_INTS_ALL;
    MyEvents[2].umask_value = MASK_ALL_STORES;

    if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 0;

    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    uint64 fb_load_hit = getNumberOfCustomEvents(0,before_sstate, after_sstate);
    uint64 loads_retired = getNumberOfCustomEvents(1,before_sstate,after_sstate);
    uint64 stores_retired = getNumberOfCustomEvents(2,before_sstate,after_sstate);

    cout << "fb_load_hit: " << fb_load_hit << endl;
    cout << "loads_retired: " << loads_retired << endl;
    cout << "stores_retired: " << stores_retired << endl;
    volatile int a = t;
    return 1;
}

bool getMemStats4 (float (func(int)), int n) {

    uint32 core = 0;
    PCM::CustomCoreEventDescription MyEvents[3];

     // L1D line replacements
    MyEvents[0].event_number = EVENT_L1D_REPLACEMENTS;
    MyEvents[0].umask_value = MASK_L1D_REPLACEMENTS;

    MyEvents[1].event_number = EVENT_L2_REQUESTS;
    MyEvents[1].umask_value = MASK_L2_REQUESTS_CODE;

    MyEvents[2].event_number = EVENT_L2_REQUESTS;
    MyEvents[2].umask_value = MASK_L2_CODE_MISSES;

    if (PCM::getInstance()->program(PCM::CUSTOM_CORE_EVENTS,&MyEvents) != PCM::Success) return 0;

    CoreCounterState before_sstate = getCoreCounterState(core);
    int t=(*func)(n);
    CoreCounterState after_sstate = getCoreCounterState(core);

    uint64 l1d_replacements = getNumberOfCustomEvents(0,before_sstate, after_sstate);
    uint64 l2_code_accesses = getNumberOfCustomEvents(1,before_sstate,after_sstate);
    uint64 l2_code_misses = getNumberOfCustomEvents(2,before_sstate,after_sstate);

    cout << "l1d_replacements: " << l1d_replacements << endl;
    cout << "l2_code_rqst_hit: " << l2_code_accesses << endl;
    cout << "l2_code_rqst_miss: " << l2_code_misses << endl;
    volatile int a = t;
    return 1;
}

#endif