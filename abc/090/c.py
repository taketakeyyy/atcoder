# -*- coding:utf-8 -*-

if __name__ == "__main__":
    N, M = list(map(int, input().split()))
    # 各マスにおいて、隣接するマス（自分含む）が奇数のマスが裏になる
    if N == 1 and M == 1:
        print("1")
    elif N <= 2 and M <= 2:
        print("0")
    elif N == 1 and M >= 3:
        print(M-2)
    elif N >= 3 and M == 1:
        print(N-2)
    else:
        print((N-2)*(M-2))
