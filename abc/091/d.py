# -*- coding:utf-8 -*-

def solver1(N, A, B):
	""" TLE """
	ans = 0
	for a in A:
		for b in B:
			ans = ans ^ (a+b)
	print(ans)

def solver2(N, A, B):
	""" 解説を実装？ """
	MAX_DIGIT = 30
	ans = [0 for i in range(MAX_DIGIT)]
	for a in A:
		for b in B:
			n = a + b
			bin_n = format(n, "b")
			length = len(bin_n)
			for i in range(length):
				if bin_n[length-1-i] == "1":
					ans[i] += 1
	# 回答する
	s = ""
	for i in range(len(ans)):
		if ans[i]%2 == 0:
			s = "0" + s
		else:
			s = "1" + s
	print(int(s, 2))

if __name__ == "__main__":
	N = int(input())
	A = list(map(int, input().split()))
	B = list(map(int, input().split()))
	#solver1(N, A, B)
	solver2(N, A, B)
