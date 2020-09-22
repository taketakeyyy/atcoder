# -*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    Ps = list(map(int, input().split()))
    max_score = sum(Ps)

    #dp[i][score] := 問iを解いたときに得点scoreになるか(True/False)
    dp = [[False for score in range(max_score+1)] for i in range(N+1)]
    dp[0][0] = True
    for i in range(1, N+1):
        for score in range(max_score+1):
            if score >= Ps[i-1]:
                dp[i][score] = dp[i-1][score] | dp[i-1][score-Ps[i-1]]
            else:
                dp[i][score] = dp[i-1][score]
    # output
    print(sum(dp[N]))
