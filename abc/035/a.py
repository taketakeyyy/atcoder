# -*- coding:utf-8 -*-

def solve():
    W, H = list(map(int, input().split()))

    a = W//4
    if a*3 == H:
        print("4:3")

    a = W//16
    if a*9 == H:
        print("16:9")

if __name__ == "__main__":
    solve()
