# -*- coding:utf-8 -*-

def solve():
    """
    「丸太の長さをX以下にする」を各丸太について行い、カット回数を計算していく方針。

    カット回数の計算は丸太一本あたりO(1)で計算できるので、全丸太でO(N)かかる。
    Xは二分探索で範囲を狭めていけば、Xの探索はO(logN)で済む。

    全体の計算量は、O(Nlog(N))
    """
    import math

    N, K = list(map(int, input().split()))
    As = list(map(int, input().split()))

    left, right = 1, 10**9
    while left != right:
        mid = (left+right)//2
        cut = 0

        for a in As:
            if a/mid > 1: cut += math.ceil(a/mid) - 1

        if cut <= K:
            # 切って良い回数を満たしている
            if left+1 == right:
                print(left)
                return
            right = mid
        else:
            # 切って良い回数を満たしていない
            if left+1 == right:
                print(right)
                return
            left = mid



if __name__ == "__main__":
    solve()
