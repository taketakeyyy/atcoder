# -*- coding:utf-8 -*-

def solve():
    S = input()
    num = int(S[3:])
    if num <= 349 and num!=316 and num!=0:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
