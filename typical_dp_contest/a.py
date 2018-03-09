#-*- coding:utf-8 -*-
import copy

if __name__ == "__main__":
	N = int(input())
	P = list(map(int, input().split()))
	# 考えられる点数をdpに格納していく
	dp = {0:1}
	for p in P:
		new_dp = copy.deepcopy(dp)
		for key in dp:
			new_dp[p+key] = 1
		dp = new_dp
	print(len(dp))
