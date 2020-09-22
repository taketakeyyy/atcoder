# -*- coding:utf-8 -*-

def solve():
    A, B = list(map(int, input().split()))
    K = (A+B)/2
    if K.is_integer():
        print(int(K))
    else:
        print("IMPOSSIBLE")

if __name__ == "__main__":
    solve()
