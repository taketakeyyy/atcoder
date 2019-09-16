# -*- coding:utf-8 -*-
import sys
import bisect

def solve():
    N, M = list(map(int, sys.stdin.readline().split()))
    X, Y = list(map(int, sys.stdin.readline().split()))
    As = list(map(int, sys.stdin.readline().split()))
    Bs = list(map(int, sys.stdin.readline().split()))
    As.sort()
    Bs.sort()

    ans = 0  # 最終的に出力する答え
    t = 0    # 現在時刻
    now_pos = "A"  # 現在の空港
    pre_a_i = 0  # 二分探索の前回のインデックス
    pre_b_i = 0  # 二分探索の前回のインデックス
    while True:
        if now_pos == "A":
            i = bisect.bisect_left(As, t, pre_a_i)
            if i >= N: break
            t = As[i] + X
            pre_a_i = i
            now_pos = "B"
        else:
            i = bisect.bisect_left(Bs, t, pre_b_i)
            if i >= M: break
            t = Bs[i] + Y
            pre_b_i = i
            now_pos = "A"
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
