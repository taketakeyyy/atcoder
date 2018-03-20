#-*- coding:utf-8 -*-
import copy

def solver1(P):
	""" 取りうる点数をkeyとして、辞書dpに格納していく方法 """
	dp = {0:True}
	for p in P:
		new_dp = copy.deepcopy(dp)
		for key in dp:
			new_dp[p+key] = True
		dp = new_dp
	print(len(dp))

def solver2(N, P):
	"""
	dp[i][score] := 問iを解いたときに得点scoreになるか(True/False)
	dp[i][score] = dp[i-1][score] | dp[i-1][score-P[i-1]] (score >= P[i-1])
	             = dp[i-1][score]                         (score <  P[i-1])
	初:dp[0][0] = True
	求:dp[N][score]=Trueとなる数
	"""
	MAX_SCORE = 0
	for p in P:
		MAX_SCORE += p
	dp = [[False for score in range(MAX_SCORE+1)] for i in range(N+1)]
	dp[0][0] = True
	for i in range(1, N+1):
		for score in range(0, MAX_SCORE+1):
			if score >= P[i-1]:
				dp[i][score] = dp[i-1][score] | dp[i-1][score-P[i-1]]
			else:
				dp[i][score] = dp[i-1][score]
	ans = 0
	for can_score in dp[N]:
		if can_score:
			ans += 1
	print(ans)


if __name__ == "__main__":
	N = int(input())
	P = list(map(int, input().split()))
	# solver1(P)
	solver2(N, P)
