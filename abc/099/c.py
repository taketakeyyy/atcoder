# -*- coding:utf-8 -*-

def solve():
	N = int(input())
	INF = 100000

	# dp[N] := N円にするのに必要な枚数の最小値
	dp = [INF] * (N+10)
	dp[0] = 0
	for n in range(1, N+1):
		# 1円使うとき
		dp[n] = min(dp[n], dp[n-1]+1)

		power = 6
		while (power <= n):
			dp[n] = min(dp[n], dp[n-power]+1)
			power *= 6
		
		power = 9
		while (power <= n):
			dp[n] = min(dp[n], dp[n-power]+1)
			power *= 9
	
	print(dp[N])



if __name__ == "__main__":
	solve()
