# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    ans = float("inf")
    for i in range(N):
        ans1 = 0
        while True:
            if A[i]%2 == 0:
                A[i] /= 2
                ans1 += 1
            else:
                break
        ans = min(ans, ans1)
    
    print(ans)

if __name__ == "__main__":
    solve()
