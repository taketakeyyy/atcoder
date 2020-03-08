# -*- coding:utf-8 -*-

def solve():
    S = input()
    hi = "hi"
    s = S.split(hi)
    for x in s:
        if x == "":
            continue
        else:
            print("No")
            return
    print("Yes")


if __name__ == "__main__":
    solve()
