# -*- coding:utf-8 -*-

def solve():
    A, B, M = list(map(int, input().split()))
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))

    ans = float("inf")
    for i in range(M):
        x, y, c = list(map(int, input().split()))
        tmp = As[x-1] + Bs[y-1] - c
        ans = min(ans, tmp)

    ans = min(ans, min(As)+min(Bs))

    print(ans)


if __name__ == "__main__":
    solve()
