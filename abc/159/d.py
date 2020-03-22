# -*- coding:utf-8 -*-

comb_dic = {}


def combination_formula(n, r):
    """nCrは、O(min(n-r, r))で実装する
    Notes:
        分子と分母がかなり大きな値になった場合、計算は遅くなるので注意
        求める値がmodをとった値でいい場合、フェルマーの小定理を使った方法が速い。
    """
    if r > n: return 0

    if n in comb_dic:
        return comb_dic[n]

    r = min(n-r, r)
    bunsi, bunbo = 1, 1
    for i in range(r):
        bunsi = bunsi*(n-i)
        bunbo = bunbo*(i+1)

    comb_dic[n] = bunsi//bunbo
    return comb_dic[n]


def solve():
    N = int(input())
    As = list(map(int, input().split()))

    dic = {}
    for a in As:
        if not a in dic:
            dic[a] = 0
        dic[a] += 1

    # combination_formula(v, 2)はくっそ早いので、
    # しゃくとりっぽく解く
    total = 0
    for key, value in dic.items():
        total += combination_formula(value, 2)

    for a in As:
        ans = total
        ans -= combination_formula(dic[a], 2)
        ans += combination_formula(dic[a]-1, 2)
        print(ans)


if __name__ == "__main__":
    solve()
