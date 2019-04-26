# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()
    K = int(input())

    t = S[K-1]
    ans = ""

    for moji in S:
        if moji == t:
            ans += moji
        else:
            ans += "*"
    print(ans)

if __name__ == "__main__":
    solve()