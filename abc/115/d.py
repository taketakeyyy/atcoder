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
"""
def solve():
    N, X = list(map(int, sys.stdin.readline().split()))

    As = [1]  # レベルiバーガーの厚さ（層の総数）
    Ps = [1]  # レベルiバーガーのパティの総数

    for i in range(N):
        As.append(As[i]*2 + 3)  # レベルが1上がると、総数は2倍+3になる
        Ps.append(Ps[i]*2 + 1)  # レベルが1上がると、パンズの数は2倍+1になる


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

if __name__ == "__main__":
    solve()
