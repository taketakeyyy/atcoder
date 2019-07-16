# -*- coding:utf-8 -*-

def solve():
    x, y = list(map(int, input().split()))

    if x < y:
        print("Better")
    else:
        print("Worse")

if __name__ == "__main__":
    solve()
