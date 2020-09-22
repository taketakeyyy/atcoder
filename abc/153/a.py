# -*- coding:utf-8 -*-
import math
def solve():
    H, A = list(map(int, input().split()))
    print(math.ceil(H/A))

if __name__ == "__main__":
    solve()
