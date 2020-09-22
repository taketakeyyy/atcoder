# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Ps = list(map(int, input().split()))

    mn = Ps[0]
    ans = 1  # 0番目は必ず答えになるので
    for i in range(1, N):
        ans += 1 if mn >= Ps[i] else 0
        mn = min(mn, Ps[i])
    print(ans)


if __name__ == "__main__":
    solve()
