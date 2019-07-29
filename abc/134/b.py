# -*- coding:utf-8 -*-
import math

def solve():
    N, D = list(map(int, input().split()))
    print(math.ceil(N/(D*2+1)))

if __name__ == "__main__":
    solve()
