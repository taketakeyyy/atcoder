# -*- coding:utf-8 -*-
import math

def solve(N):
    bin_str = bin(N)
    if bin_str[0] == "-":
        bin_str = bin_str[3:]
    else:
        bin_str = bin_str[2:]

    print(bin_str)
    exit()
    j = 0
    for k in range(len(bin_str)-1, -1, -1):
        ans = bin_str[i] * j

def solve2(N):
    """
    1011
    11000101011001101110100010101
    """
    if N <= 0:
        N *= -1
        print(bin(N)[2:])
        exit()

    ans = ""
    while True:
        if N%(-2) == 0:
            ans = "0" + ans
        else:
            ans = "1" + ans
        N = math.floor(N/(-2))
        if N == 0:
            ans = "1" + ans
            break
    print(ans)

if __name__ == "__main__":
    N = int(input())

    solve2(N)
