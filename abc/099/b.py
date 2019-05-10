# -*- coding:utf-8 -*-

def solve():
    a, b = list(map(int, input().split()))

    diff = b - a
    n = diff -1
    left_h = (1+n)*n/2
    ans = int(left_h - a)
    print(ans)

if __name__ == "__main__":
    solve()
