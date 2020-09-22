# -*- coding:utf-8 -*-

def solve():
    X, N = list(map(int, input().split()))
    Ps = list(map(int, input().split()))

    if N == 0:
        print(X)
        return

    setP = set(Ps)

    ans = float("inf")
    for x in range(0, 102):
        if not x in setP:
            if abs(X-ans) > abs(X-x):
                ans = x

    print(ans)


if __name__ == "__main__":
    solve()
