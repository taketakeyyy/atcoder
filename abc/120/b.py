# -*- coding:utf-8 -*-

def solve():
    A, B, K = list(map(int, input().split()))

    for i in range(101, 0, -1):
        if A%i==0 and B%i==0:
            K -= 1
            if K==0:
                print(i)
                return



if __name__ == "__main__":
    solve()
