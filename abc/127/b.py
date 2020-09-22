# -*- coding:utf-8 -*-

def solve():
    r, D, x2000 = list(map(int, input().split()))
    x = [0] * 11
    x[0] = x2000
    for i in range(1, 11):
        x[i] = r*x[i-1] - D
        print(x[i])

if __name__ == "__main__":
    solve()
