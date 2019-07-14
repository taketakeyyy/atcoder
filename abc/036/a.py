# -*- coding:utf-8 -*-
import math
def solve():
    A, B = list(map(int, input().split()))
    print(math.ceil(B/A))


if __name__ == "__main__":
    solve()
