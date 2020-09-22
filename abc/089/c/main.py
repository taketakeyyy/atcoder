#-*- coding:utf-8 -*-

if __name__ == "__main__":
	N = int(input())
	m = 0
	a = 0
	r = 0
	c = 0
	h = 0
	for i in range(N):
		name = input()
		if name[0] == "M":
			m += 1
		elif name[0] == "A":
			a += 1
		elif name[0] == "R":
			r += 1
		elif name[0] == "C":
			c += 1
		elif name[0] == "H":
			h += 1
	# 3人を選ぶ方法を全探索する
	ans  = m*a*r + m*a*c + m*a*h + m*r*c + m*r*h + m*c*h
	ans += a*r*c + a*r*h + a*c*h
	ans += r*c*h
	print(ans)
