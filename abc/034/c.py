# -*- coding:utf-8 -*-
import sys
from math import factorial

def combination_formula(n, r):
    return factorial(n) // (factorial(r)*factorial(n-r))


"""解説
横6マス、縦2マスの格子を考える。

高橋くんは、右に1マスか、上に1マスのどちらかにしか移動できない。

ということは、

- - - - - - | | の重複組み合わせ = C(8, 2) が答え。
"""


def solve():
    """ PyPyでAC（最悪ケースのみPythonでTLE） """
    W, H = list(map(int, sys.stdin.readline().split()))
    MOD = 1000000007

    ans = combination_formula((W-1)+(H-1), H-1)
    print(ans%MOD)


if __name__ == "__main__":
    solve()
