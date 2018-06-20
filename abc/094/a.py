# -*- coding:utf-8 -*-
def solve(A, B, X):
	if A > X:
		print("NO")
		return
	if A+B >= X:
		print("YES")
		return
	print("NO")

if __name__ == "__main__":
	A, B, X = list(map(int, input().split()))
	solve(A, B, X)
