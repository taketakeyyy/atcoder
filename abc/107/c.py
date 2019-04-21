# -*- coding:utf-8 -*-
import copy

INF = 2*(10**8)+1
memo = INF  # メモ化用変数

def solve():
    N, K = list(map(int, input().split(" ")))
    X = [0]
    X.extend(list(map(int, input().split(" "))))
    X.sort()

    # 幅優先探索すればいいんじゃね？

    def dfs(depth, cost, i, Xs):
        global memo
        if depth == K:
            memo = min(cost, memo)
            return cost
        
        if cost >= memo:
            # 探索を打ち切る
            return INF
        
        ret1, ret2 = INF, INF
        if i+1 < len(Xs):
            # 右に移動
            tmpCost = abs(Xs[i] - Xs[i+1])
            tmpXs = copy.deepcopy(Xs)
            del tmpXs[i]
            ret1 = dfs(depth+1, cost+tmpCost, i, tmpXs)
        if i-1 >= 0:
            # 左に移動
            tmpCost = abs(Xs[i] - Xs[i-1])
            tmpXs = copy.deepcopy(Xs)
            del tmpXs[i]
            ret2 = dfs(depth+1, cost+tmpCost, i-1, tmpXs)
        
        return min(ret1, ret2)

    # 0座標のインデックスは？
    for i in range(len(X)):
        if X[i] == 0:
            break
    ans = dfs(0, 0, i, X)
    print(ans)


if __name__ == "__main__":
    solve()