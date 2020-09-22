# -*- coding:utf-8 -*-

def prime_factor(n):
    """因数分解して因数のみを取得する"""
    if n <= 1: return set()

    ans = set()
    i = 2
    while i*i <= n:
        while n%i == 0:
            if not i in ans:
                ans.add(i)
            n //= i
        i += 1

    if n != 1:
        ans.add(n)
    return ans

def solve():
    import sys
    N = int(sys.stdin.readline())
    As = list(map(int, sys.stdin.readline().split()))

    pf_sets = []
    for a in As:
        pf_set = prime_factor(a)
        pf_sets.append(pf_set)


    # pairwiseにできるかを調べる
    is_pairwise = True
    a_set = set()
    for pf_set in pf_sets:
        if len(a_set & pf_set) != 0:
            # すでに因数が存在するならpairwiseになれない
            is_pairwise = False
            break
        a_set |= pf_set

    if is_pairwise:
        print("pairwise coprime")
        return

    # setwiseにできるかを調べる
    is_setwise = False
    base_pf_set = pf_sets[0]
    for pf_set in pf_sets[1:]:
        base_pf_set &= pf_set

        if len(base_pf_set) == 0:
            is_setwise = True
            break

    if is_setwise:
        print("setwise coprime")
        return

    print("not coprime")

if __name__ == "__main__":
    solve()
