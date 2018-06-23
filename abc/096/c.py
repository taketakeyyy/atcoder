# -*- coding: utf-8 -*-

def solve(s, K):
	# TLE: 1 <= K <= 5 �Ƃ������������A���܂���Ɏ}�؂��ł����͂�
	substrings = []
	substrings_dict = {}

	s_len = len(s)
	for j in range(1, s_len+1):
		for i in range(0, s_len):
			substring = s[i:i+j]
			if substring in substrings_dict:
				continue
			substrings_dict[substring] = True
			substrings.append(substring)
	substrings.sort()
	print(substrings)
	return substrings[K-1]

if __name__ == "__main__":
	s = input()
	K = int(input())
	print(solve(s, K))
