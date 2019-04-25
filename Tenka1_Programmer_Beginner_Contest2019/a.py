# -*- coding:utf-8 -*-

def solve():
    A, B, C = list(map(int, input().split()))
    if A <= C and C <= B:
        print("Yes")
    elif A >= C and C >= B:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()