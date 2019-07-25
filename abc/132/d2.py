# -*- coding:utf-8 -*-
from math import factorial

def permutation_formula(n, r):
    return factorial(n) // factorial(n-r)

def combination_formula(n, r):
    return factorial(n) // (factorial(r)*factorial(n-r))

def solve():
    N, K = list(map(int, input().split()))
    B, R = K, N-K
    MOD = 10**9+7

    for i in range(1, K+1):
        if R+1-i < 0:
            print(0)
            continue
        
        ans = combination_formula(R+1, i)
        ans %= MOD

        if B-i > 0:
            ans *= combination_formula(B-i+i-1, i-1)
            ans %= MOD
        print(ans)



if __name__ == "__main__":
    solve()
