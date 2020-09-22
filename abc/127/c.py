# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))

    l_max = 0
    r_min = float("inf")
    for i in range(M):
        l, r = list(map(int, input().split()))
        l_max = max(l_max, l)
        r_min = min(r_min, r)

    print(max(r_min-l_max+1, 0))    



if __name__ == "__main__":
    solve()
