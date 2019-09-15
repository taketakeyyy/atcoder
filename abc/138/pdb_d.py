# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(1000000)

"""解説
いもす法っぽいことする
[入力例]
4 3
1 2
2 3
2 4
2 10
1 100
3 1

[出力例]
"""
def solve():
    #N, Q = list(map(int, input().split()))
    N, Q = 4, 3
    to = [[] for _ in range(N)]  # 木

    """
    for _ in range(N-1):
        a, b = list(map(int, input().split()))
        a, b = a-1, b-1  # 0始まりになるように
        to[a].append(b)  # 無向グラフになるように両方に加える
        to[b].append(a)  # 無向グラフになるように両方に加える
    """

    to = [[1], [0, 2, 3], [1], [1]]
    print(to)

    """
    ans = [0 for _ in range(N)]
    for _ in range(Q):
        p, x = list(map(int, input().split()))
        p = p-1  # 0始まりになるように
        ans[p] += x
    """

    ans = [100, 10, 1, 0]
    print(ans)

    def dfs(v, p=-1):
        for u in to[v]:
            if u==p: continue
            ans[u] += ans[v]  # いもす法っぽい累積和をする
            dfs(u, v)

    dfs(0)

    print(*ans)


if __name__ == "__main__":
    solve()
