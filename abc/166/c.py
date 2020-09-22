# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    Hs = list(map(int, input().split()))

    goods = [1 for _ in range(N)]
    for _ in range(M):
        a, b = list(map(int, input().split()))
        a, b = a-1, b-1
        if Hs[a] > Hs[b]:
            goods[b] = 0
        elif Hs[b] > Hs[a]:
            goods[a] = 0
        else:
            goods[a] = 0
            goods[b] = 0

    print(sum(goods))


if __name__ == "__main__":
    solve()
