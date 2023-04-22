# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    splitted = S.split("-")
    ans = 0
    for s in splitted:
        ans = max(ans, len(s))

    if "-" in S and "o" in S:
        print(ans)
    else:
        print(-1)

if __name__ == "__main__":
    solve()
