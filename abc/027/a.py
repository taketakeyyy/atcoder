# -*- coding:utf-8 -*-

def solve():
    l1, l2, l3 = list(map(int, input().split()))
    if l1 == l2:
        print(l3)
    elif l1 == l3:
        print(l2)
    elif l2 == l3:
        print(l1)


if __name__ == "__main__":
    solve()
