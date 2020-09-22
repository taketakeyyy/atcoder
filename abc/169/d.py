# -*- coding:utf-8 -*-


def solve():
    N = int(input())

    """
    ■ 解法
    N = p^{e1} * p^{e2} * p^{e3} ...
    と因数分解できるとき、
    z = p_i^{1}, p_i^{2}, ...
    としていくのが最適なので、それを数えていく

    (例) N = 2^2 * 3^2 * 5 * 7
    のとき、
    2,3,5,7の4回割れる。（6で割る必要はない）

    ■ 計算量
    素因数分解するのに、O(√N)
    割れる回数を計算するのはたかだか素因数分解するより少ないはずなので、
    全体としてはO(√N+α)くらいでしょ（適当）
    """
    def prime_factor(n):
        """素因数分解する"""
        i = 2
        ans = {}
        while i*i <= n:
            while n%i == 0:
                if not i in ans:
                    ans[i] = 0
                ans[i] += 1
                n //= i
            i += 1
        if n != 1:
            ans[n] = 1
        return ans

    pf = prime_factor(N)

    ans = 0
    for key, value in pf.items():
        i = 1
        while value-i >= 0:
            value -= i
            ans += 1
            i += 1
    print(ans)


if __name__ == "__main__":
    solve()
