# -*- coding:utf-8 -*-

def solve():
    N, Q = list(map(int, input().split(" ")))
    S = input()
    L, R = [], []
    for i in range(Q):
        l, r = list(map(int, input().split(" ")))
        L.append(l)
        R.append(r)
    
    # 累積話で解く
    accumulations = [0] * N

    for i in range(1, N):
        if S[i-1]+S[i] == "AC":
            accumulations[i] = accumulations[i-1] + 1
        else:
            accumulations[i] = accumulations[i-1]

    for i in range(Q):
        if L[i]-1 == 0:
            print(accumulations[R[i]-1])
            continue
        else:
            print(accumulations[R[i]-1] - accumulations[L[i]-1])
            continue


if __name__ == "__main__":
    solve()