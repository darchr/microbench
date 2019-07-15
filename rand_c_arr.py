#!/usr/bin/python3

import random
import argparse
import sys

parser = argparse.ArgumentParser(description='Generate a random (or otherwise) C Array')
parser.add_argument('-l','--len', default=16384, type=int, help='Size of Random Array')
parser.add_argument('-r','--range', default=2, type=int, help='Upper Bound on Random Value -- 2 for Binary')
parser.add_argument('-d', '--data_type', default='not_set')
parser.add_argument('--non_random',action='store_true')
parser.add_argument('-o','--output', default='randArr.h')
parser.add_argument('-n','--name', default='randArr')

args = parser.parse_args()

if args.data_type=='not_set':
  if args.range==2:
    args.data_type='char'
  else:
    args.data_type='int'

#out_file = open(args.output,'w')
print(args.data_type + " " + args.name + "[] = {\n", end='')

for i in range(0,args.len):
  if args.non_random:
    print(str(i%args.range), end='')
  else:
    print(str(random.randint(0,args.range-1)), end='')

  if i!=args.len-1:
    print(",", end='')

  if args.range<=9:
    if  i % 64 == 63:
      print("\n", end='')
  elif args.range<=99:
    if  i % 32 == 31:
      print("\n", end='')
  else :
    if i % 16 == 15:
      print("\n", end='')


print("};", end='')

#out_file.close()
