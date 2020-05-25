# -*- coding:utf-8 -*-

def solve():
    import sys

    MOD = 998244353
    N, M, K = list(map(int, sys.stdin.readline().split()))

    """
    xの組を作るとする
    (1) グループ数: N-x
    (2) グループの色の割り当て方：M(M-1)**(N-1)
    (3) グループの分け方：(N-1)C(x)
    """

    bunsi_memo = {}
    bunbo_memo = {}
    pow_memo = {}
    def combination_formula_MOD(n, r, MOD):
        """nCrを O(min(n-r, r)) で高速に計算する"""
        def _inv(x, MOD):
            """xの逆元を返す"""
            if not (x, MOD-2) in pow_memo:
                pow_memo[(x, MOD-2)] = pow(x, MOD-2, MOD)
            return pow_memo[(x, MOD-2)]

        if n < r: return 0

        r = min(n-r, r)
        bunsi, bunbo = 1, 1
        if not r in bunsi_memo:
            for i in range(r):
                bunsi = bunsi*(n-i)%MOD
                bunbo = bunbo*(i+1)%MOD
            bunsi_memo[r] = bunsi
            bunbo_memo[r] = bunbo
        bunsi, bunbo = bunsi_memo[r], bunbo_memo[r]
        return (bunsi*_inv(bunbo, MOD))%MOD


    ans = 0
    col = M
    for x in range(N-1, -1, -1):
        if x <= K:
            now = col%MOD
            now = (now * combination_formula_MOD(N-1, x, MOD))%MOD
            ans += now
            ans %= MOD

        col *= (M-1)
        col %= MOD

    print(ans)


if __name__ == "__main__":
    solve()
