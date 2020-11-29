# -*- coding:utf-8 -*-

def solve():
    import bisect

    N, M = list(map(int, input().split()))
    H = list(map(int, input().split()))
    W = list(map(int, input().split()))
    H.sort()
    W.sort()

    # 生徒iが先生と組むときの最小身長差を求める
    diffs = [0 for _ in range(N)]
    for i in range(N):
        j = bisect.bisect_left(W, H[i])
        if j == 0:
            diffs[i] = abs(H[i]-W[0])
        elif j == M:
            diffs[i] = abs(H[i]-W[-1])
        else:
            diffs[i] = min(abs(H[i]-W[j-1]), abs(H[i]-W[j]))

    # まず、H[0]が先生と組むときを計算する
    total = 0
    for i in range(1, len(H), 2):
        total += H[i+1]-H[i]
    ans = total+diffs[0]

    # 次に、H[1]~が先生と組むときの計算をする（しゃくとり法で）
    for i in range(1, N):
        if i%2==1:
            total += H[i]-H[i-1]
        else:
            total -= H[i]-H[i-1]
        ans = min(ans, total+diffs[i])

    print(ans)


if __name__ == "__main__":
    solve()
