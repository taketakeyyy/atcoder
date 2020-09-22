# -*- coding:utf-8 -*-

def solve():
    A, B, C, K = list(map(int, input().split()))

    if A >= K:
        print(K)
        return

    total = A
    K -= A

    if B >= K:
        print(total)
        return

    K -= B

    total += -K

    print(total)


if __name__ == "__main__":
    solve()
