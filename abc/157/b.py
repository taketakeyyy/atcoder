# -*- coding:utf-8 -*-

def solve():
    A1s = list(map(int, input().split()))
    A2s = list(map(int, input().split()))
    A3s = list(map(int, input().split()))
    As = []
    As.append(A1s)
    As.append(A2s)
    As.append(A3s)
    N = int(input())
    bingo = [[False for _ in range(3)] for __ in range(3)]

    for _ in range(N):
        b = int(input())

        for i in range(3):
            for j in range(3):
                if b == As[i][j]:
                    bingo[i][j] = True

    # 判定
    for i in range(3):
        if bingo[i][0] and bingo[i][1] and bingo[i][2]:
            print("Yes")
            return
        if bingo[0][i] and bingo[1][i] and bingo[2][i]:
            print("Yes")
            return
    if (bingo[0][0] and bingo[1][1] and bingo[2][2] or
        bingo[0][2] and bingo[1][1] and bingo[2][0]):
        print("Yes")
        return
    print("No")



if __name__ == "__main__":
    solve()
