# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))
    """戦略
    長方形の条件は、縦の2辺の長さが等しくて、横の2辺の長さが等しい。
    自分と同じ数字のものを複数持つ数字を、大きいものから2つ取ってくれば、その2つの数字が長方形の2辺になる。   
    """

    A.sort(reverse=True)
    a = A[0]
    for i in range(1, len(A)):
        if a == A[i]:
            break
        a = A[i]

    if i >= len(A)-1:
        print(0)
        return

    b = A[i+1]
    for j in range(i+2, len(A)):
        if b == A[j]:
            break
        b = A[j]

    if j == len(A):
        print(0)
        return
    
    print(a*b)

if __name__ == "__main__":
    solve()
