# -*- coding:utf-8 -*-
from math import factorial

MOD = 10**9+7

def combination_formula(n, r):
    _max, _min = max(n-r, r), min(n-r, r)
    bunsi, bunbo = 1, 1
    for i in range(_min):
        bunsi *= (n-i)
        bunbo *= (i+1)
        bunsi %= MOD
        bunbo %= MOD
    # フェルマーの小定理を使って、modの世界のbunsi/bunboを計算する
    # 1/bunbo ≡ bunbo^{p-2} より、
    bunbo = pow(bunbo, MOD-2, MOD)
    ans = (bunsi*bunbo) % MOD
    return ans

def solve():
    n, a, b = list(map(int, input().split()))
    ans = pow(2, n, MOD)
    ans -= 1  # nC0を除外
    ans -= combination_formula(n, a)
    ans -= combination_formula(n, b)
    while ans < 0:
        ans += MOD
    print(ans)


if __name__ == "__main__":
    solve()
