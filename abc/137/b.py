# -*- coding:utf-8 -*-

def solve():
    K, X = list(map(int, input().split()))
    left = X - (K-1)
    right = X + (K-1)

    s = ""
    for i in range(left, right+1):
        s += "{} ".format(i)
    print(s[:-1])


if __name__ == "__main__":
    solve()
