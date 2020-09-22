# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    MOD = 10**9+7
    ans = pow(10,N,MOD)
    ans = (ans - (2*pow(9,N,MOD))%MOD)%MOD
    ans = (ans + pow(8,N,MOD))%MOD
    print(ans)


if __name__ == "__main__":
    solve()
