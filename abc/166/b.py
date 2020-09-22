# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))

    sunukes = [0 for _ in range(N)]
    for k in range(K):
        d = int(input())
        As = list(map(int, input().split()))
        for a in As:
            a = a-1
            sunukes[a] = 1

    ans = N - sum(sunukes)
    print(ans)


if __name__ == "__main__":
    solve()
