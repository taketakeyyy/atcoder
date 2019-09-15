# -*- coding:utf-8 -*-

"""解法
公式PDF

A_1＋ A_2 ＋ ... A_N = X_1 + X_2 + ... + X_N = S とする

(X_i + X_{i+1})/2 = A_i より

X_i + X_{i+1} = 2A_i

X1 = S - (X_2 + ... + X_N)
   = S - 2(A_2 + A_4 + A_{N-1})

これにより、X_1, X_2 ... を順に求めればよいが、O(N^2)は難しい

そこでO(N)で解くために

X_i + X_{i+1} = 2A_i より
X_{i+1} = 2 * A_i - X_i

の漸化式をつくれるので、それを解く
"""
import sys


def solve():
    N = int(sys.stdin.readline())
    As = list(map(int, sys.stdin.readline().split()))

    S = sum(As)
    Xs = [0]*N
    # 初期状態を決める(Xs[0])
    Xs[0] = S - 2 * sum(As[1:N:2])

    for i in range(N-1):
        Xs[i+1] = 2*As[i] - Xs[i]

    print(*Xs)


if __name__ == "__main__":
    solve()
