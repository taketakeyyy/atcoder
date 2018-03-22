# -*- coding:utf-8 -*-

def solver1(N, A, B):
	""" TLE """
	ans = 0
	for a in A:
		for b in B:
			ans = ans ^ (a+b)
	print(ans)


if __name__ == "__main__":
	N = int(input())
	A = list(map(int, input().split()))
	B = list(map(int, input().split()))
	#solver1(N, A, B)
