#-*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    A = list(map(int, input().split()))
    A.sort(reverse=True)
    alice = 0
    bob   = 0
    for i in range(len(A)):
        if i%2 == 0:
            alice += A[i]
        else:
            bob += A[i]
    print(alice - bob)
