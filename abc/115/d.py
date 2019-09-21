# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(10000)

"""考え方
L0 : P
L1 : BPPPB
L2 : BBPPPBPBPPPBB
L3 : BBBPPPBPBPPPBBPBBPPPBPBPPPBBB
L4 : ...

・レベルが1上がると、Pの数は2倍+1になる
・レベルが1上がると、総数は2倍+3になる


レベルiバーガーの厚さ（層の総数）をa_iとする
レベルiバーガーに含まれるパティの総数をp_iとする
「レベルNバーガーの下からX層に含まれるパティの枚数」をf(N,X)とする。

・N = 0のとき
f(0,X) = 1

・N >= 1のとき
f(N-1, Y)がわかると仮定すると、

(1) X = 1のとき、f(N,X) = 0 (一番下のバンだけ)

(2) 1 < X <= 1 + a_{i-1} のとき、f(N,X) = f(N-1, X-1)

i=2のとき、L2のときで
BBPPPB PBPPPBB
BPPPBB|ここまでのとき

(3) X = 2 + a_{i-1}のとき、f(N,X) = p_{i-1}+1
???


https://www.youtube.com/watch?v=1ONpCPN-IR8
"""
def solve():
    N, X = list(map(int, sys.stdin.readline().split()))

    As = [1]  # レベルiバーガーの厚さ（層の総数）
    Ps = [1]  # レベルiバーガーのパティの総数

    for i in range(N):
        As.append(As[i]*2 + 3)  # レベルが1上がると、総数は2倍+3になる
        Ps.append(Ps[i]*2 + 1)  # レベルが1上がると、パティの数は2倍+1になる


    def _dfs(depth, x):
        """ レベルdepthバーガーの、下からX層に含まれるパティの枚数を返す """
        if depth == 0:
            return 0 if x <= 0 else 1
        elif x <= 1 + As[depth-1]:
            # 一番下のパン + その上のレベル N-1 バーガー + その上のパティ
            return _dfs(depth-1, x-1)
        else:
            # (前略) + その上のパティ + その上のレベル N-1 バーガーの下から x-2-As[depth-1]層
            return Ps[depth-1] + 1 + _dfs(depth-1, x-2-As[depth-1])

    ans = _dfs(N, X)

    print(ans)


def solve2():
    N, X = list(map(int, sys.stdin.readline().split()))

    As = [1]  # レベルiバーガーの厚さ（層の総数）（必ず奇数）
    Ps = [1]  # レベルiバーガーのパティの総数

    for i in range(N):
        As.append(As[i]*2 + 3)  # レベルが1上がると、総数は2倍+3になる
        Ps.append(Ps[i]*2 + 1)  # レベルが1上がると、パティの数は2倍+1になる

    def f(n, x):
        """レベルnバーガーの下からx層食べたときの、食べたパティの総数"""
        if n == 0:
            return 0 if x <= 0 else 1

        median = (As[n]+1)//2

        if x < median:
            return f(n-1, x-1)
        elif x == median:
            return Ps[n-1] + 1
        elif x > median:
            return Ps[n-1] + 1 + f(n-1, x-median)

    ans = f(N, X)

    print(ans)


def solve3():
    N, X = list(map(int, sys.stdin.readline().split()))

    As = [1]  # レベルiバーガーの厚さ（層の総数）（必ず奇数）
    Ps = [1]  # レベルiバーガーのパティの総数

    for i in range(N):
        As.append(As[i]*2 + 3)  # レベルが1上がると、総数は2倍+3になる
        Ps.append(Ps[i]*2 + 1)  # レベルが1上がると、パティの数は2倍+1になる

    # dp[i][x] := レベルiバーガーの下からx層に含まれているパティの総数
    dp = [[0]*(X+1) for _ in range(N+1)]
    dp[0][0] = 0
    for i in range(1, X+1):
        dp[0][i] = 1

    # 漸化式を解く
    for i in range(1, N+1):
        median = (As[i]+1)//2
        for x in range(X+1):
            if x < median:
                dp[i][x] = dp[i-1][x-1]
            elif x == median:
                dp[i][x] = Ps[i-1] + 1
            else:
                dp[i][x] = Ps[i-1] + 1 + dp[i-1][x-median]

    print(dp[N][X])



if __name__ == "__main__":
    solve3()
