# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    K = int(input())
    X = int(input())
    Y = int(input())

    if N >= K:
        ans = X*K + Y*(N-K)
    else:
        ans = X*N
    print(ans)        

if __name__ == "__main__":
    solve()
