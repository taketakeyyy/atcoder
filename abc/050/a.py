# -*- coding:utf-8 -*-

def solve():
    A, op, B = input().split()
    A, B = int(A), int(B)

    if op == "+":
        print(A+B)
    else:
        print(A-B)

if __name__ == "__main__":
    solve()
