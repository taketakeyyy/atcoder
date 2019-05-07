# -*- coding:utf-8 -*-
import math

def solve():
    K = int(input())
    odd = math.ceil(K/2)
    even = math.floor(K/2)

    print(odd*even)

if __name__ == "__main__":
    solve()
