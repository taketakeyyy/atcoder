# -*- coding:utf-8 -*-

INF = 10**9

def dfs(depth, a, b, c, A, B, C, N, ls):
    if depth == N:
        # 全ての竹を選び終わったら、延長魔法と短縮魔法を使ってA,B,Cの長さにする
        return abs(a-A) + abs(b-B) + abs(c-C) - 30 if min(a, b, c) > 0 else INF
    ret0 = dfs(depth+1, a, b, c, A, B, C, N, ls)  # 使わない
    ret1 = dfs(depth+1, a+ls[depth], b, c, A, B, C, N, ls) + 10  # Aに使う
    ret2 = dfs(depth+1, a, b+ls[depth], c, A, B, C, N, ls) + 10  # Bに使う
    ret3 = dfs(depth+1, a, b, c+ls[depth], A, B, C, N, ls) + 10  # Cに使う
    
    return min(ret0, ret1, ret2, ret3)


def solve():
    N, A, B, C = [int(x) for x in input().split(" ")]
    ls = []
    for _ in range(N):
        ls.append(int(input()))
    
    print(dfs(0,0,0,0, A, B, C, N, ls))


if __name__ == "__main__":
    solve()