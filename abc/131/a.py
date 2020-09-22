# -*- coding:utf-8 -*-

def solve():
    S = input()
    pre_moji = S[0]
    for i in range(1, len(S)):
        if S[i] == pre_moji:
            print("Bad")
            return
        pre_moji = S[i]
    print("Good")


if __name__ == "__main__":
    solve()
