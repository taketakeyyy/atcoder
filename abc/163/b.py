# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    As = list(map(int, input().split()))

    total = sum(As)

    if N - total < 0:
        print(-1)
    else:
        print(N-total)


if __name__ == "__main__":
    solve()
