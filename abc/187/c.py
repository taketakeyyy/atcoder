# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    dic = {}

    for i in range(N):
        s = input()
        if s[0] == "!":
            dic[s] = True
            if s[1:] in dic:
                print(s[1:])
                return
        else:
            dic[s] = True
            if "!"+s in dic:
                print(s)
                return

    print("satisfiable")


if __name__ == "__main__":
    solve()
