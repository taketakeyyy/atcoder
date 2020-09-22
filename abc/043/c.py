# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    # 全探索余裕(累積和で高速化可能？)
    ans = float("inf")
    for i in range(-100, 100+1):
        cost = 0
        for j in range(N):
            # 全てiに書き換える
            cost += (i - A[j])**2
        ans = min(ans, cost)
    
    print(ans)


if __name__ == "__main__":
    solve()
