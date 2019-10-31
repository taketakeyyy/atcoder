# -*- coding:utf-8 -*-

def solve():
    A, B = list(map(int, input().split()))

    if 1 <= A <= 9 and 1 <= B <= 9:
        print(A*B)
    else:
        print(-1)

if __name__ == "__main__":
    solve()
