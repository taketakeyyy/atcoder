# -*- coding:utf-8 -*-

if __name__ == "__main__":
	N, M, X = list(map(int, input().split()))
	As = list(map(int, input().split()))
	cost = 0
	for A in As:
		if X > A:
			break
		cost += 1
	print(max(cost, M-cost))
