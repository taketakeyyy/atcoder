# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    A = list(map(int, input().split()))

    # しゃくとり法
    ans = 0
    total = 0
    for i in range(N):
        total += A[i]
        if total >= K:
            ans += N - i
            r = i
            break

    if ans == 0:
        print(ans)
        return

    for l in range(1, N):
        total -= A[l-1]
        if total >= K:
            ans += N - r
            continue
        while True:
            r += 1
            if r == N:
                print(ans)
                return
            total += A[r]
            if total >= K:
                ans += N - r
                break
    print(ans)


if __name__ == "__main__":
    solve()
