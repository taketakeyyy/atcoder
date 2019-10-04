# -*- coding:utf-8 -*-

def solve():
    a = int(input())
    b = int(input())
    if a == b:
        print(0)
    else:
        print(b - (a%b))

if __name__ == "__main__":
    solve()
