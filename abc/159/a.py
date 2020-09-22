# -*- coding:utf-8 -*-
def combination_formula(n, r):
    """nCrは、O(min(n-r, r))で実装する
    Notes:
        分子と分母がかなり大きな値になった場合、計算は遅くなるので注意
        求める値がmodをとった値でいい場合、フェルマーの小定理を使った方法が速い。
    """
    if r > n:
        return 0

    r = min(n-r, r)
    bunsi, bunbo = 1, 1
    for i in range(r):
        bunsi = bunsi*(n-i)
        bunbo = bunbo*(i+1)
    return bunsi//bunbo


def solve():
    N, M = list(map(int, input().split()))

    # 奇数＋奇数 または偶数＋偶数
    ans = combination_formula(N, 2) + combination_formula(M,2)
    print(ans)


if __name__ == "__main__":
    solve()
