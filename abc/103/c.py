# -*- coding:utf-8 -*-

if __name__ == '__main__':
    N = int(input())
    A = list(map(int, input().split()))
    f = 0
    # 実装
    sum = 0
    for a in A:
        sum += (a - 1)
    print(sum)
