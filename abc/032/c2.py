# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    S = []
    for _ in range(N):
        s = int(input())
        S.append(s)

    if 0 in S:
        print(N)
        return


    # しゃくとり法
    ans = 0
    left = 0
    total = 1
    for right in range(N):
        total *= S[right]
        if total <= K:
            ans = max(ans, right-left+1)
            continue
        while total > K:
            total //= S[left]
            left += 1
            if left > right: break

    print(ans)


if __name__ == "__main__":
    solve()
