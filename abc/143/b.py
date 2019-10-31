# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Ds = list(map(int, input().split()))

    ans = 0
    for i in range(N):
        for j in range(i+1, N):
            ans += Ds[i]*Ds[j]
    print(ans)

if __name__ == "__main__":
    solve()
