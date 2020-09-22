# -*- coding:utf-8 -*-

def solve(a, b, c, d):
	# (1) AとCが通信可能
	if abs(a-c) <= d:
		print("Yes")
		return
	# (2) AとB、BとCが通信可能
	if (abs(a-b) <= d) and (abs(b-c) <= d):
		print("Yes")
		return
	print("No")

if __name__ == "__main__":
	a, b, c, d = list(map(int, input().split()))
	solve(a, b, c, d)
