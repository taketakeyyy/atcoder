#-*- coding:utf-8 -*-

if __name__ == "__main__":
	N = int(input())
	reds  = []
	blues = []
	for i in range(N):
		x, y = list(map(int, input().split()))
		reds.append([x, y])
	for i in range(N):
		x, y = list(map(int, input().split()))
		blues.append([x, y])
