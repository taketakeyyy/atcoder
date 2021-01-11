# -*- coding:utf-8 -*-

def solve():
    X, Y = list(map(int, input().split()))
    if (X<Y and X+3>Y) or (X>Y and Y+3>X):
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
