# -*- coding:utf-8 -*-

def solve():
    s = input()
    lenS = len(s)
    ans = s[0] + str(lenS-2) + s[-1]
    print(ans)

if __name__ == "__main__":
    solve()
