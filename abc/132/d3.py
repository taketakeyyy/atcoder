# -*- coding:utf-8 -*-
from math import factorial

def combination_formula(n, r):
    return factorial(n) // (factorial(r)*factorial(n-r))

def solve():
    N, K = list(map(int, input().split()))
    R, B = N-K, K
    MOD = 10**9+7

    for i in range(1, K+1):
        if R+1 < i:
            print(0)
            continue

        ans = combination_formula(R+1, i)%MOD  # R+1の隙間のうち、i個の箇所に青玉を入れる組み合わせ

        restB = B - i

        ans *= combination_formula(restB+(i-1), i-1)%MOD  # 残りの青玉とi-1個のしきいの、重複組み合わせ
        print(ans%MOD)


if __name__ == "__main__":
    solve()