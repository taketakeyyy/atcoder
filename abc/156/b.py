# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    ans = 0
    while N != 0:
        N //=K
        ans += 1
    print(ans)


if __name__ == "__main__":
    solve()
