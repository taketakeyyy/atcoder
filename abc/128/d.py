# -*- coding:utf-8 -*-
from collections import deque
"""解説
全探索

左からL個、右からR個宝石を取り、K-(L+R)個の宝石を筒に詰めるとき方針として、

・筒に詰める宝石は絶対値の大きい負の値のもの

あとは全探索
"""

def solve():
    N, K = list(map(int, input().split()))
    V = list(map(int, input().split()))

    ans = 0
    r = min(N, K)
    for a in range(r+1):  # 左から取る個数
        for b in range(r+1):  # 右から取る個数
            if r < a+b: continue

            t = V[:a] + V[::-1][:b]  # 左からa個、右からb個とった宝石を「持っているリストt」にぶちこむ
            t.sort(reverse=True)

            for _ in range(K-a-b):
                if len(t) > 0 and t[-1] < 0:
                    t.pop()
                    continue
                break
            ans = max(ans, sum(t))

    print(ans)



if __name__ == "__main__":
    solve()
