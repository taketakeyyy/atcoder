# -*- coding:utf-8 -*-

def solve():
    T = int(input())
    for _ in range(T):
        L, R = list(map(int, input().split()))
        # ans = 0
        # for B in range(L, R+1):
        #     if 2*B <= R:
        #         ans += 1
        #         ans += (R-2*B)*2
        if 2*L <= R:
            n = (R//2)-L+1
            d = 4  # 等差数列の和
            a = (R-2*(L+n-1))*2+1
            S = n*(2*a+(n-1)*d)//2
            print(S)
        else:
            print(0)


if __name__ == "__main__":
    solve()
