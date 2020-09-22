# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    sets = set()
    for i in range(1, 10):
        for j in range(1, 10):
            sets.add(i*j)

    if N in sets:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
