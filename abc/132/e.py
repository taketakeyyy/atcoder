# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))

    """
    dp[i][j] := i回目の操作で頂点jに到達できるか否か
    to[v]: 頂点vから1回の操作で到達できる頂点のリスト

    """

    to = {}
    for i in range(M):
        u, v = list(map(int, input().split()))
        u, v = u-1, v-1
        if not u in to:
            to[u] = []
        to[u].append(v)    

    dp = [j for j in range(0, N)]
    for i in range(N):






if __name__ == "__main__":
    solve()
