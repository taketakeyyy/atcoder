# -*- coding:utf-8 -*-
import sys

def solve():
    A, B, C = map(int, sys.stdin.readline().split())
    if ((A==B and A!=C and B!=C) or
        (B==C and B!=A and C!=A) or
        (C==A and C!=B and A!=B)):
        print("Yes")
        return
    print("No")

if __name__ == "__main__":
    solve()
