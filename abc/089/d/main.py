#-*- coding:utf-8 -*-
import math

if __name__ == "__main__":
	H, W, D = list(map(int, input().split()))
	masu_d = {}
	for i in range(H):
		inputs = list(map(int, input().split()))
		for j in range(W):
			masu_d[inputs[j]] = [i, j]

	Q = int(input())
	L = []
	R = []
	for i in range(Q):
		l, r = list(map(int, input().split()))
		L.append(l)
		R.append(r)
	# 総和計算開始
	for i in range(Q):
		ans = 0
		if L[i] == R[i]:
			print(int(ans))
			continue
		ans += math.fabs(masu_d[L[i]][0]-masu_d[R[i]][0]) + math.fabs(masu_d[L[i]][1]-masu_d[R[i]][1])
		print(int(ans))
