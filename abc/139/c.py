# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Hs = list(map(int, input().split()))

    # Hs[0]から線形探索でOK
    ans, total = 0, 0
    for i in range(1, N):
        if Hs[i-1] >= Hs[i]:
            total += 1
            ans = max(ans, total)
        else:
            total = 0

    print(ans)


if __name__ == "__main__":
    solve()
