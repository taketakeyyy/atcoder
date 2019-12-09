# -*- coding:utf-8 -*-

def solve():
    M, N = list(map(int, input().split()))
    ans = M - (M//N)*(N-1)
    print(ans)

if __name__ == "__main__":
    solve()
