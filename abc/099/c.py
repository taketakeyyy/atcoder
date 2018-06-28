# -*- coding:utf-8 -*-

def make_list(N, n):
	lists = []
	a = n
	while True:
		if N >= a:
			lists.append(a)
			a *= n
			continue
		break
	return lists

def solve(N):
	#1, 6, 9
	nines = make_list(N, 9)
	sixs  = make_list(N, 6)
	nums  = sixs + nines
	nums.sort(reverse=True)

	rest  = N
	count = 0
	for n in nums:
		if rest >= n:
			print("{} * {}回 = {}".format(n, rest//n, rest))
			count += rest//n
			rest   = rest%n
	print(count+rest)

if __name__ == "__main__":
	N = int(input())
	solve(N)
