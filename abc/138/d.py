# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(1000000)

"""解説
いもす法っぽいことする

[注意]
input()だとTLEしたので、それより少し高速なsys.stdin.readline()を使うとACした。


[入力例]
4 3
1 2
2 3
2 4
2 10
1 100
3 1

[出力例]
100 110 111 110


"""
def solve():
    N, Q = map(int, sys.stdin.readline().split())
    to = [[] for _ in range(N)]  # 木

    for _ in range(N-1):
        a, b = map(int, sys.stdin.readline().split())
        a, b = a-1, b-1  # 0始まりになるように
        to[a].append(b)  # 無向グラフになるように両方に加える
        to[b].append(a)  # 無向グラフになるように両方に加える

    #print(to)

    ans = [0 for _ in range(N)]
    for _ in range(Q):
        p, x = map(int, sys.stdin.readline().split())
        p = p-1  # 0始まりになるように
        ans[p] += x

    #print(ans)

    def dfs(v, p=-1):
        for u in to[v]:
            if u==p: continue
            ans[u] += ans[v]  # いもす法っぽい累積和をする
            dfs(u, v)

    dfs(0)

    print(*ans)


if __name__ == "__main__":
    solve()
