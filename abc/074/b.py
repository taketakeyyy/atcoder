# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    K = int(input())
    X = list(map(int, input().split()))

    ans = 0
    for i in range(N):
        ans += min(X[i]*2, (K-X[i])*2)
    
    print(ans)

if __name__ == "__main__":
    solve()
