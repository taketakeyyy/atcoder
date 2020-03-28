# -*- coding:utf-8 -*-

def solve():
    K, N = list(map(int, input().split()))
    As = list(map(int, input().split()))

    As.sort()
    if len(As) == 1:
        print(0)
        return

    Ls = []  # 隣家間の距離をぶちこんでいく
    for i in range(1, len(As)):
        Ls.append(As[i]-As[i-1])
    Ls.append(As[0] + K-As[-1])

    Ls.sort()
    print(K-Ls[-1])


if __name__ == "__main__":
    solve()
