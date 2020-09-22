# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S, T = input().split()

    ans = ""
    for i in range(len(S)):
        ans += S[i]+T[i]
    print(ans)


if __name__ == "__main__":
    solve()
