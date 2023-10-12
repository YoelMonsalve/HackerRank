#!/bin/python3

import math
import os
import random
import re
import sys

# Calculates the result of query `q` applied over arr
def calculateQueryResult(arr:list, q:int):
    #arr = list(map(lambda x: x+q, arr))
    arr = [x+q for x in arr]
    return arr, sum(map(abs, arr));
    #return arr, 0

#
# Complete the 'playingWithNumbers' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER_ARRAY arr
#  2. INTEGER_ARRAY queries
#

def playingWithNumbers(arr, queries):
    result = [0] * len(queries)
    for i in range(len(queries)):
        arr, result[i] = calculateQueryResult(arr, queries[i])
    return result;

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    arr = list(map(int, input().rstrip().split()))

    q = int(input().strip())

    queries = list(map(int, input().rstrip().split()))

    result = playingWithNumbers(arr, queries)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()

