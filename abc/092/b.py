#-*- coding:utf-8 -*-
import math
def how_many_choco(A, D):
    """ 何個チョコ食ったか返す
    nA + 1 <= Dを満たすnを求める
    """
    return math.floor((D-1)/A) + 1

if __name__ == "__main__":
    N = int(input())
    D, X = list(map(int, input().split()))
    eaten = 0
    for i in range(N):
        A = int(input())
        eaten += how_many_choco(A, D)
    print(X + eaten)
