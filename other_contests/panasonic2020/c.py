# -*- coding:utf-8 -*-

def solve():
    # 式変形する
    a, b, c = list(map(int, input().split()))

    if c-a-b >= 0 and 4*a*b < (c-a-b)**2:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
