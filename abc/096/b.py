# -*- coding:utf-8 -*-
import math

def solve(X):
	ans = X
	# b^p = ans‚Æ‚È‚éans‚ğ’T‚·
	for b in range(2, X):
		p = math.log(ans, b) # ¸“x‚Å€‚Ê(log(100, 10)‚È‚Ç)
		if float.is_integer(p):
			return ans
	return 1

def solve2(X):
	# ‘S’Tõ
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
