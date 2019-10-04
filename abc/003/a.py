# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    ans = 0
    for i in range(1, N+1):
        ans += 10000*i * (1/N)
    print(ans)

if __name__ == "__main__":
    solve()
