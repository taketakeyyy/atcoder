# -*- coding:utf-8 -*-

def solve():
    s = input()
    t = input()

    s = list(s)
    s.sort()
    s2 = ""
    for moji in s:
        s2 += moji

    t = list(t)
    t.sort(reverse=True)
    t2 = ""
    for moji in t:
        t2 += moji
    
    if s2 < t2:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
