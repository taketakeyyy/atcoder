# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    d = dict()
    for i in range(N):
        s = list(input())
        s.sort()
        s = tuple(s)
        if s in d:
            d[s] += 1
            continue
        d[s] = 0

    ans = 0
    for key, val in d.items():
        if val == 0:
            continue
        ans += (val+1)*val//2

    print(ans)

if __name__ == "__main__":
    solve()
