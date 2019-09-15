# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    d = {}  # d[v] = [index]
    for i in range(N):
        a = int(input())
        if not a in d:
            d[a] = []
        d[a].append(i)
    
    d_keys = list(d.keys())
    d_keys.sort()

    b = 0
    d2 = {}
    for key in d_keys:
        d2[b] = d[key]
        b += 1

    ans = [0] * N
    for i, lst in d2.items():
        for v in lst:
            ans[v] = i

    for v in ans:
        print(v)



if __name__ == "__main__":
    solve()
