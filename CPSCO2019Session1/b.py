# -*- coding:utf-8 -*-

def solve():
    S = input()

    dic = dict()
    for moji in S:
        if not moji in dic:
            dic[moji] = 0
        dic[moji] += 1

    cnt = dic[S[0]]
    for v in dic.values():
        if cnt != v:
            print("No")
            return
    print("Yes")


if __name__ == "__main__":
    solve()
