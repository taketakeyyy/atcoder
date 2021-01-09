# -*- coding:utf-8 -*-

"""

"""

def solve():
    N, M = list(map(int, input().split()))
    paths = [[] for _ in range(N)]
    happys = {}

    for _ in range(M):
        a, b, h = list(map(int, input().split()))
        paths[a-1].append(b-1)
        paths[b-1].append(a-1)
        happys[(a-1, b-1)] = h
        happys[(b-1, a-1)] = h

    # dp[i][S] := 現在地がiで、訪問済みの町集合がSのときのコストの最大値
    dp = [[0 for _ in range(pow(2,N))] for __ in range(N)]

    for bit in range(pow(2,N)):
        for i in range(N):  # 現在の町i
            if not (bit>>i&1): continue  # iは訪れていないならcontinue
            for j in paths[i]:
                if bit>>j&1: continue  # jはすでに訪れているならcontinue
                # iが訪問済みで、jはまだ訪れていないなら・・・
                dp[j][bit|1<<j] = max(dp[j][bit|1<<j], dp[i][bit]+happys[(i,j)])

    # 答えを探す
    ans = 0
    for bit in range(pow(2,N)):
        for i in range(N):
            ans = max(ans, dp[i][bit])

    print(ans)


if __name__ == "__main__":
    solve()
