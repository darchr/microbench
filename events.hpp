#ifndef EVENTS_H
#define EVENTS_H

/* This file defines macros for various hardware events
to reuse them with ease */

// Front end events
#define EVENT_BR_RETIRED 0xC4
#define EVENT_BR_RETIRED_MISP 0xC5
#define MASK_BR_RETIRED_ALL 0x04
#define MASK_BR_RETIRED_COND 0x01
#define MASK_BR_RETIRED_NOT_TAKEN 0x10
#define MASK_BR_RETIRED_NEAR_TAKEN 0x20
#define MASK_BR_RETIRED_FAR_BRANCH 0x40

#define EVENT_INST_RETIRED 0xC6
// all front-end events have same mask, need to configure MSRvalues to record these events, but pcm doesn't allow this configuration.
#define MASK_L1I_MISS 0x01 // Retired Instructions who experienced Instruction L1 Cache true miss

// Execution core events

// Memory events
#define EVENT_MEM_INTS_ALL 0xD0
#define MASK_ALL_LOADS 0x81 // All retired load instructions
#define MASK_ALL_STORES 0x82
#define MASK_STLB_MISS_LOADS 0x11
#define MASK_STLB_MISS_STORES 0x12
#define MASK_LOCK_LOADS 0x21 // Retired load instructions with locked access
#define MASK_SPLIT_LOADS 0x41 // Counts retired load instructions that split across a cacheline boundary
#define MASK_SPLIT_STORES 0x42

#define EVENT_L1D_REPLACEMENTS 0x51 // Counts L1D data line replacements including opportunistic replacements, and replacements that require stall-for-replace or block-for-replace
#define MASK_L1D_REPLACEMENTS 0x01

#define EVENT_ITLB 0x85
#define MASK_ITLB_MISS_STLB_HIT 0x20

#define EVENT_FB_FULL 0x48
#define MASK_FB_FULL 0x02 // Number of times a request needed a FB entry but there was no entry available for it

#define EVENT_MEM_LOADS 0xD1
#define MASK_L1_LOAD_HITS 0x01
#define MASK_L2_LOAD_HITS 0x02
#define MASK_L3_LOAD_HITS 0x04
#define MASK_FB_LOAD_HITS 0x40 // Retired load instructions which data sources were load missed L1 but hit FB due to preceding miss to the same cache line with data not ready
#define MASK_L1_LOAD_MISS 0x08
#define MASK_L2_LOAD_MISS 0x10
#define MASK_L3_LOAD_MISS 0x20

#define EVENT_L2_REQUESTS 0x24
#define MASK_L2_REQUESTS 0xFF // All L2 requests
#define MASK_L2_MISSES 0x3F // All requests that miss L2 cache
#define MASK_L2_REQUESTS_DATA 0xE7 // Demand requests to L2 cache
#define MASK_L2_DATA_MISS 0x27 // All requests that miss L2 cache
#define MASK_L2_REQUESTS_LOAD 0xE1 // Counts the number of demand Data Read requests (including requests from L1D hardware prefetchers). These loads may hit or miss L2 cache. Only non rejected loads are counted
#define MASK_L2_LOAD_RQST_HITS 0xC1 // Counts the number of demand Data Read requests, initiated by load instructions, that hit L2 cache
#define MASK_L2_LOAD_RQST_MISSES 0x21 // Counts the number of demand Data Read requests that miss L2 cache. Only not rejected loads are counted
#define MASK_L2_REQUESTS_STORE 0xE2 // Counts the total number of RFO (read for ownership) requests to L2 cache. L2 RFO requests include both L1D demand RFO misses as well as L1D RFO prefetches
#define MASK_L2_STORE_HITS 0xC2 // Counts the RFO (Read-for-Ownership) requests that hit L2 cache, this indicates store hits
#define MASK_L2_STORE_MISSES 0x22 // Counts the RFO (Read-for-Ownership) requests that miss L2 cache
#define MASK_L2_REQUESTS_CODE 0xE4 // Counts the total number of L2 code requests
#define MASK_L2_CODE_HITS 0xC4 // Counts L2 cache hits when fetching instructions, code reads
#define MASK_L2_CODE_MISSES 0x24 // Counts L2 cache misses when fetching instructions
#define MASK_L2_REQUESTS_PF 0xF8 // Counts the total number of requests from the L2 hardware prefetchers
#define MASK_L2_REQUESTS_PF_HITS 0xD8 // Counts requests from the L1/L2/L3 hardware prefetchers or Load software prefetches that hit L2 cache
#define MASK_L2_REQUESTS_PF_MISSES 0x38 // Counts requests from the L1/L2/L3 hardware prefetchers or Load software prefetches that miss L2 cache

#endif