# -*- coding:utf-8 -*-
from math import factorial

def solve():
    N, M = list(map(int, input().split()))
    MOD = 10**9+7
    """
    ありうるパターンは、
    
    ・NとMが同数
    ・NとMの差が1

    （例）
    ・2 2
    犬 猿 犬 猿
    この場合、犬と猿の位置を入れ替えたパターンもあるので×2

    ・2 3
    犬 猿 犬 猿 犬

    組み合わせの数は、順列の公式を使う
    
    ・順列の公式
    異なるn個のものからr個を取り出し並べる場合の数は
    nPr = n(n-1)(n-2)...(n-r+1) = n!/(n-r)!
    """

    def permutation_formula(n, r):
        return factorial(n) // factorial(n-r)

    if N == M:
        ans = (permutation_formula(N, N)%MOD) * (permutation_formula(M, M)%MOD) * 2
        print(ans%MOD)
        return
    elif abs(N-M) == 1:
        ans = (permutation_formula(N, N)%MOD) * (permutation_formula(M, M)%MOD)
        print(ans%MOD)
    else:
        print(0)
        return


if __name__ == "__main__":
    solve()
