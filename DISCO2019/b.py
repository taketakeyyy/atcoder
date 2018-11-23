# -*- coding: utf-8 -*-
import math

def main():
    N = int(input())
    if N%2 == 0:
        # 偶数
        syou = math.floor(N/2)
        print((N-2)*syou)
        exit()
    else:
        # 奇数
        N = N - 1
        syou = math.floor(N/2)
        print((N-2)*syou+1)
        exit()


if __name__ == '__main__':
    main()
