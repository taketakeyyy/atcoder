# -*- coding:utf-8 -*-

def solve():
    a, b, c = list(map(int, input().split()))

    if a+b == c or b+c==a or c+a==b:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
