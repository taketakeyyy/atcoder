#-*- coding:utf-8 -*-

def solver1(N, reds, blues):
	""" 解説を実装
	青点のx座標が最も小さいものは、赤点のy座標の最も大きいものとペアになって良い
	"""
	sorted_reds  = sorted(reds, key=lambda x:x[1], reverse=True)  # y座標で降順ソート
	sorted_blues = sorted(blues, key=lambda x:x[0])  # x座標で昇順ソート
	ans = 0
	for i in range(N):
		for j in range(len(sorted_blues)):
			if (sorted_reds[i][0] < sorted_blues[j][0] and
			    sorted_reds[i][1] < sorted_blues[j][1]):
				ans += 1
				del sorted_blues[j]
				break
	print(ans)

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

	solver1(N, reds, blues)
