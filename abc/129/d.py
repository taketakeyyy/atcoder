# -*- coding:utf-8 -*-

def solve():
    H, W = list(map(int, input().split()))
    grid = []
    for i in range(H):
        grid.append(list(input()))

    for h in range(H):
        seq_num = 0  # 連続で.が続いた数
        for w in range(W):
            if grid[h][w] == ".":
                seq_num += 1
            else:
                
                seq_num = 0



if __name__ == "__main__":
    solve()
