# -*- coding:utf-8 -*-

def solve():
    import sys

    N = int(sys.stdin.readline())

    total = 0
    dic = {}
    for i in range(1, 10):
        for j in range(1, 10):
            total += i*j
            if not i*j in dic:
                dic[i*j] = []
            s = str(i) + " x " + str(j)
            dic[i*j].append(s)

    rest = total - N

    dic[rest].sort()
    for value in dic[rest]:
        print(value)


if __name__ == "__main__":
    solve()
