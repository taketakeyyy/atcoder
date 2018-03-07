#-*- coding:utf-8 -*-
import math

if __name__ == "__main__":
	H, W, D = list(map(int, input().split()))
	masu = {}
	for i in range(H):
		inputs = list(map(int, input().split()))
		for j in range(W):
			masu[inputs[j]] = [i, j]

	Q = int(input())
	L = []
	R = []
	for i in range(Q):
		l, r = list(map(int, input().split()))
		L.append(l)
		R.append(r)
	# i=D+1 ~ H*W の累積和Sを求める
	S = [0] * (H*W+1)
	for i in range(D+1, H*W+1):
		S[i] = S[i-D] + abs(masu[i][0]-masu[i-D][0]) + abs(masu[i][1]-masu[i-D][1])
	# 回答する
	for i in range(Q):
		print(S[R[i]] - S[L[i]])
