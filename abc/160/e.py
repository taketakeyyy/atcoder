# -*- coding:utf-8 -*-

def solve():
    X, Y, A, B, C = list(map(int, input().split()))
    P = list(map(int, input().split()))
    Q = list(map(int, input().split()))
    R = list(map(int, input().split()))
    P.sort(), Q.sort(), R.sort()
    ALL = P[len(P)-X:] + Q[len(Q)-Y:] + R
    ALL.sort(reverse=True)
    print(sum(ALL[0:X+Y]))

if __name__ == "__main__":
    solve()
