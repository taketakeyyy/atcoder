# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    syain = {}  # syain[i] = {n1, n2}  # 上司iが持つ直属の部下はn1, n2
    for i in range(N):
        b = int(input())
        if not b in syain:
            syain[b] = set()
        syain[b].add(i+2)



if __name__ == "__main__":
    solve()
