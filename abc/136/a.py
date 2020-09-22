# -*- coding:utf-8 -*-

def solve():
    A,B,C = list(map(int, input().split()))
    print(max(C-(A-B), 0))

if __name__ == "__main__":
    solve()
