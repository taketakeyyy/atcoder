# -*- coding:utf-8 -*-
import math

def solve(X):
	ans = X
	# b^p = ansとなるansを探す
	for b in range(2, X):
		p = math.log(ans, b) # 精度で死ぬ(log(100, 10)など)
		if float.is_integer(p):
			return ans
	return 1

def solve2(X):
	# 全探索
	for x in range(X, 1, -1):
		for p in range(2, x):
			for b in range(2, x):
				bp = b**p
				if bp == x:
					return x
				if bp >= x:
					break
	return 1

if __name__ == "__main__":
	X = int(input())
	print(solve2(X))
