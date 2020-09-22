# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Vs = list(map(int, input().split()))

    Vs.sort()

    new_v = (Vs[0]+Vs[1])/2

    if N == 2:
        print(new_v)
        return

    for i in range(2, N):
        new_v = (new_v+Vs[i])/2

    print(new_v)


if __name__ == "__main__":
    solve()
