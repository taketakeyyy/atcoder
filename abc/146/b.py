# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    ans = ""
    for moji in S:
        a = ord(moji) + N
        if a > ord("Z"):
            a -= ord("Z") - ord("A") + 1
        ans += chr(a)
    print(ans)

if __name__ == "__main__":
    solve()
