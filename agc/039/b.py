# -*- coding:utf-8 -*-
import numpy as np

def solve():
    N = int(input())
    masu = []
    for _ in range(N):
        S = input()
        masu.append(list(map(int, S)))
    masu = np.array(masu)



if __name__ == "__main__":
    solve()
