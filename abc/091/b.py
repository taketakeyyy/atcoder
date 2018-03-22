#-*- coding:utf-8 -*-

if __name__ == "__main__":
	N = int(input())
	blue_cards = [input() for i in range(N)]
	M = int(input())
	red_cards = [input() for i in range(M)]
	# 全探索(O(N*N*M), 高々10^6)
	max_money = 0
	for word in blue_cards:
		money = 0
		for blue in blue_cards:
			if word == blue:
				money += 1
		for red in red_cards:
			if word == red:
				money -= 1
		if money > max_money:
			max_money = money
	print(max_money)
