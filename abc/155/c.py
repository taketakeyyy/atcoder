# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    dic = {}

    max_num = -1
    for i in range(N):
        S = input()
        if not S in dic: dic[S] = 0
        dic[S] += 1

        if dic[S] > max_num:
            max_num = dic[S]

    anss = []
    for key, value in dic.items():
        if value == max_num:
            anss.append(key)

    anss.sort()

    for ans in anss:
        print(ans)


if __name__ == "__main__":
    solve()
