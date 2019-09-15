# -*- coding:utf-8 -*-

def solve():
    L, R = list(map(int, input().split()))
    MOD = 2019

    ans = float("inf")
    if R-L <= MOD-1:
        for i in range(L, R+1):
            for j in range(i+1, R+1):
                ans = min(ans, i*j%MOD)
    else:
        # 必ず0をかけることになるので
        ans = 0

    print(ans)


if __name__ == "__main__":
    solve()
