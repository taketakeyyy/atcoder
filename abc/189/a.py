# -*- coding:utf-8 -*-

def solve():
    S = input()
    if S[0]==S[1] and S[1]==S[2]:
        print("Won")
    else:
        print("Lost")


if __name__ == "__main__":
    solve()
