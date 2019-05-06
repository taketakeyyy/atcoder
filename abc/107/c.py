# -*- coding:utf-8 -*-

"""解説
https://www.youtube.com/watch?v=5O4k1n5Ejzw

区間を考える問題

-30 -10 0 10 20 50

・K = 3のとき、

0座標を必ず含める、ある連続するK個のロウソクについて考える

・-30 -10 0 10
・-10 0 10 20
・0 10 20 50

左端と右端に到達する最小値を求めていけばよくて、間のロウソクは無視してよい（必ず移動中に火をつけるので）

すべての場合について求めて、その中の最小値が答え
"""
def solve():
    N, K = list(map(int, input().split()))
    X = list(map(int, input().split()))
    if 0 in X:
        # 0座標にロウソクがあるなら、火をつけるロウソクをひとつ減らしてよい
        K -= 1
    else:
        X.append(0)
    X.sort()

    origin_i = X.index(0)
    left_i = max(origin_i-K, 0)

    INF = 10**12
    ans = INF
    while left_i <= origin_i:
        if left_i+K < len(X):
            tmp1 = abs(X[left_i]-0)*2 + abs(X[left_i+K]-0)
            tmp2 = abs(X[left_i]-0) + abs(X[left_i+K]-0)*2
        else:
            break
        ans = min(ans, tmp1, tmp2)
        left_i += 1
    print(ans)

if __name__ == "__main__":
    solve()

