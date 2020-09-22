# -*- coding:utf-8 -*-
import math

if __name__ == "__main__":
    N, K = list(map(int, input().split()))
    if(N%K == 0):
        print("0")
    else:
        print("1")
