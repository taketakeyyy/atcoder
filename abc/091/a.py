#-*- coding:utf-8 -*-

if __name__ == "__main__":
	A, B, C = list(map(int, input().split()))
	if A+B >= C:
		print("Yes")
	else:
		print("No")
