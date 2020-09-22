# -*- coding:utf-8 -*-
import math

if __name__ == "__main__":
    N = int(input())

    if N == 7:
        print("Yes")
        exit()

    max_7 = math.floor(N / 7)
    for i in range(max_7, -1, -1):
        rest = N - i*7
        if rest%4 == 0:
            print("Yes")
            exit()

    print("No")
