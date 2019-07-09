# -*- coding:utf-8 -*-

def solve():
    n, x = list(map(int, input().split()))
    print(min(x-1, n-x))

if __name__ == "__main__":
    solve()
