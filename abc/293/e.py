# -*- coding:utf-8 -*-

def solve():
    A, X, M = map(int, input().split())
    if A == 1:
        print(X%M)
    else:
        bunsi = pow(A,X,M*(A-1))-1
        bunsi %= M*(A-1)
        bunbo = A-1
        ans = bunsi // bunbo
        print(ans)

if __name__ == "__main__":
    solve()
