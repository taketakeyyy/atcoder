# -*- coding:utf-8 -*-

def solve():
    N, K, M = map(int, input().split())
    As = list(map(int, input().split()))

    x = N*M-sum(As)

    if x > K:
        print(-1)
    else:
        print(max(0, x))


if __name__ == "__main__":
    solve()
