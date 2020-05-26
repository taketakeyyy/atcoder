# -*- coding:utf-8 -*-

def solve():
    MOD = 2019
    S = input()

    """解説AC"""
    # A列を作成
    As = []
    d = 1
    for moji in S[::-1]:
        a = (int(moji)*d)%MOD
        As.append(a)
        d = (d*10)%MOD

    # 累積和を作成
    ruiseki = [0]
    for i, a in enumerate(As):
        r = (ruiseki[i] + a)%MOD
        ruiseki.append(r)

    # ruiseki[i] ≡ ruiseki[j] (mod 2019) となる総数を数える
    ruiseki_dic = {}  # combinationの計算でもいける
    ans = 0
    for r in ruiseki:
        if not r in ruiseki_dic:
            ruiseki_dic[r] = 1
        else:
            ans += ruiseki_dic[r]
            ruiseki_dic[r] += 1

    print(ans)


def solve2():
    MOD = 2019
    S = input()

    """解説AC"""
    # A列を作成
    As = []
    d = 1
    for moji in S[::-1]:
        a = (int(moji)*d)%MOD
        As.append(a)
        d = (d*10)%MOD

    # 累積和を作成
    ruiseki = [0]
    for i, a in enumerate(As):
        r = (ruiseki[i] + a)%MOD
        ruiseki.append(r)

    # ruiseki[i] ≡ ruiseki[j] (mod 2019) となる総数を数える
    # combinationの計算でもいける
    ruiseki_dic = {}
    ans = 0
    for r in ruiseki:
        if not r in ruiseki_dic:
            ruiseki_dic[r] = 0
        ruiseki_dic[r] += 1

    def combination_formula(n, r):
        """nCrは、O(min(n-r, r))で実装する
        Notes:
            分子と分母がかなり大きな値になった場合、計算は遅くなるので注意
            求める値がmodをとった値でいい場合、フェルマーの小定理を使った方法が速い。
        """
        if n < r: return 0

        r = min(n-r, r)
        bunsi, bunbo = 1, 1
        for i in range(r):
            bunsi = bunsi*(n-i)
            bunbo = bunbo*(i+1)
        return bunsi//bunbo

    ans = 0
    for v in ruiseki_dic.values():
        if v < 2: continue
        ans += combination_formula(v,2)

    print(ans)


if __name__ == "__main__":
    solve()
