# -*- coding:utf-8 -*-

def solve():
    A, B, K = list(map(int, input().split()))

    if K > A:
        K -= A
        A = 0
        if K > B:
            B = 0
        else:
            B -= K
    else:
        A -= K

    print(A, B)


if __name__ == "__main__":
    solve()
