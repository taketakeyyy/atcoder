# -*- coding:utf-8 -*-
from itertools import combinations
def solve():
    N, M = list(map(int, input().split()))
    denkyus = []
    for i in range(M):
        a = list(map(int, input().split()))
        k = a[0]
        switches = a[1:]
        denkyus.append(switches)
    P = list(map(int, input().split()))

    petterns = products(range(2), repeat=M)

    ans = 0
    for pettern in petterns:






if __name__ == "__main__":
    solve()
