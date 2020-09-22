# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    ans = 0
    for i in range(N):
        l, r = list(map(int, input().split()))
        ans += (r-l+1)
    print(ans)

if __name__ == "__main__":
    solve()
