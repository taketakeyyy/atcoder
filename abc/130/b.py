# -*- coding:utf-8 -*-

def solve():
    N, X = list(map(int, input().split()))
    L = list(map(int, input().split()))

    ans = 1
    d = 0

    for i in range(0, N):
        d = d + L[i]
        if not d <= X: break
        ans += 1
    
    print(ans)


if __name__ == "__main__":
    solve()
