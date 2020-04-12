# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    while N!=0:
        d0 = N%10
        if d0 == 7:
            print("Yes")
            return
        N //= 10
    print("No")
    return

if __name__ == "__main__":
    solve()
