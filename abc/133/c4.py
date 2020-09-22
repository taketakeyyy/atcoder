# -*- coding:utf-8 -*-

def solve():
    L, R = list(map(int, input().split()))
    MOD = 2019
    
    if R-L >= MOD:
        print(0)
        return

    L %= MOD
    R %= MOD

    if R < L:
        print(0)
        return
    
    ans = MOD
    for i in range(L, R+1):
        for j in range(i+1, R+1):
            ans = min(ans, i*j%MOD)
    print(ans)

if __name__ == "__main__":
    solve()
