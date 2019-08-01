# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    D = list(map(int, input().split()))

    n = N
    while True:
        k = str(n)
        ok = True
        for ki in k:
            if int(ki) in D:
                ok = False
        if ok:
            print(n)
            return
        n += 1



if __name__ == "__main__":
    solve()
