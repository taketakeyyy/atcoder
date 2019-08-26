# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    As = list(map(int, input().split()))

    # しゃくとり法で解く
    k = K-1
    total = 0
    for i in range(k+1):
        total += As[i]
    ans = total

    if N == K:
        print(ans)
        return

    for i in range(1, N):
        if i+k == N:
            break
        total += As[i+k] - As[i-1]
        ans += total

    print(ans)

if __name__ == "__main__":
    solve()
