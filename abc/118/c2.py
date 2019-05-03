# -*- coding:utf-8 -*-
import fractions

def solve():
    N = input()
    A = list(map(int, input().split()))

    # Aの要素を使って、1以上の作成可能な最も小さい値を作る。それが答え。
    # というか最大公約数が答え。

    ans = A[0]
    for i in range(1, N):
        ans = fractions.gcd(ans, A[i])
    print(ans)

if __name__ == "__main__":
    solve()
