# -*- coding:utf-8 -*-

def solve():
    N, K = map(int, input().split())

    N = N%K

    while True:
        preN = N
        N = abs(N-K)
        if N > preN:
            print(preN)
            return

if __name__ == "__main__":
    solve()
