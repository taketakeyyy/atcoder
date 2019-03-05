# -*- coding:utf-8 -*-

INF = 10**9

def solve():
    N, A, B, C = [int(x) for x in input().split(" ")]
    ls = []
    for _ in range(N):
        ls.append(int(input()))

    def _dfs(depth, a, b, c):
        if depth == N:
            # 全ての竹を選び終わったら、延長魔法と短縮魔法を使ってA,B,Cの長さにする
            return abs(a-A) + abs(b-B) + abs(c-C) - 30 if min(a, b, c) > 0 else INF
        ret0 = _dfs(depth+1, a, b, c)  # 使わない
        ret1 = _dfs(depth+1, a+ls[depth], b, c) + 10  # Aに使う
        ret2 = _dfs(depth+1, a, b+ls[depth], c) + 10  # Bに使う
        ret3 = _dfs(depth+1, a, b, c+ls[depth]) + 10  # Cに使う
        
        return min(ret0, ret1, ret2, ret3)

    print(_dfs(0,0,0,0))


if __name__ == "__main__":
    solve()