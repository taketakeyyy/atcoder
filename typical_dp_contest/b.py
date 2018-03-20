#-*- coding:utf-8 -*-

if __name__ == "__main__":
	A, B  = list(map(int, input().split()))
	left  = list(map(int, input().split()))
	right = list(map(int, input().split()))
	# l,‚’–‡c‚Á‚Ä‚¢‚é‚Æ‚«‚Ìæè‚Ì“_”‚ÌÅ‘å’ldp‚Í
	# Šï””Ô dp[l][r] = MAX(dp[l-1][r] + left.pop(0), dp[l][r-1] + right.pop(0)
	# ‹ô””Ô dp[l][r] = MIN(dp[l-1][r], dp[l][r-1])
	# dp[0][r] = dp[0][r-1] + right.pop(0)
	# dp[l][0] = dp[l-1][0] + left.pop(0)
	dp = [[0 for i in range(A+1)] for j in range(B+1)]
	dp[0][0] = 0
	for l in range(A+1):
		for r in range(B+1):
			dp[l][r] =
