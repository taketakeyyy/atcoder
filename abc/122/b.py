# -*- coding:utf-8 -*-

def solve():
    S = input()

    ans = 0
    tmp = 0
    for s in S:
        if s=="A" or s=="C" or s=="G" or s=="T":
            tmp += 1
        else:
            ans = max(ans, tmp)
            tmp = 0
    ans = max(ans, tmp)
    print(ans)


if __name__ == "__main__":
    solve()
