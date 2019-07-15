# -*- coding:utf-8 -*-

def solve():
    L, R = list(map(int, input().split()))
    MOD = 2019

    if (R-L) >= 2019:
        print(0)
        return

    L %= MOD
    R %= MOD

    ans = MOD
    for i in range(L, R+1):
        for j in range(i+1, R+1):
            ans = min(ans, (i*j)%MOD)
            if ans == 0:
                print(ans)
                return
    print(ans)
    

if __name__ == "__main__":
    solve()
