# -*- coding:utf-8 -*-

def solve():
    a, b, c = list(map(int, input().split()))
    penki_set = set()
    penki_set.add(a)
    penki_set.add(b)
    penki_set.add(c)
    print(len(penki_set))

if __name__ == "__main__":
    solve()
