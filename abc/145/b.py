# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()
    if N%2 != 0:
        print("No")
        return

    l_str = S[0:N//2]
    r_str = S[N//2:]

    if l_str == r_str:
        print("Yes")
        return

    print("No")

if __name__ == "__main__":
    solve()
