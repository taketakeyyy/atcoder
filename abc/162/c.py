# -*- coding:utf-8 -*-
from math import gcd

def solve():
    K = int(input())
    ans = 0

    # 3つ同じ値のとき
    for i in range(1, K+1):
        ans += i

    # 2つ同じ値のとき
    for i in range(1, K+1):
        for j in range(1, K+1):
            if i==j: continue
            ans += gcd(i, j)*3

    # すべて異なる値のとき
    for i in range(1, K+1):
        for j in range(i+1, K+1):
            for k in range(j+1, K+1):
                ans += gcd(gcd(i,j),k)*6

    print(ans)


if __name__ == "__main__":
    solve()
