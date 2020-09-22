# -*- coding:utf-8 -*-

def solve():
    N = int(input())

    # Nの深さの偶奇によって戦略が変わる
    # 根を0として、
    # 深さが偶数の場合、高橋は右に、青木は左に行きたい
    # 深さが奇数の場合、高橋は左に、青木は右に行きたい
    depth = 0
    NN = N
    while NN != 1:
        NN //= 2
        depth += 1

    x = 1
    turn = "Takahashi"
    if depth%2 == 0:
        # 高橋は右に、青木は左に行きたい
        while True:
            if x > N: break

            if turn == "Takahashi":
                x = 2*x + 1
                turn = "Aoki"
            else:
                x = 2 * x
                turn = "Takahashi"
    else:
        # 高橋は左に、青木は右に行きたい
        while True:
            if x > N: break

            if turn == "Takahashi":
                x = 2 * x
                turn = "Aoki"
            else:
                x = 2 * x + 1
                turn = "Takahashi"

    print(turn)





if __name__ == "__main__":
    solve()
