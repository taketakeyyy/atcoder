# -*- coding:utf-8 -*-


def solve():
    """BFSで解く
    """
    import sys
    from collections import deque

    """
        0             400
      0 +--------------+
        |              |
        |              |
        |              |
        |              |
    400 +--------------+

    無限に広がる二次元グリッドなので、「0~400のマス以内しか移動できない」わけではない。
    外周を周ったら到達可能ということもあり得る。なので、外周分の縦横ぞれぞれ+αずつする。（金の動きで+1で足りるか？怖いので+α）

    """
    BASE = 250
    MX = 500
    N, X, Y = list(map(int, sys.stdin.readline().split()))
    X, Y = X+BASE, Y+BASE
    grid = [[0 for _ in range(MX+1)] for __ in range(MX+1)]  # すべての座標に+250している
    dist = [[float("inf") for _ in range(MX+1)] for __ in range(MX+1)]  # すべての座標に+250している

    for _ in range(N):
        x, y = list(map(int, sys.stdin.readline().split()))
        grid[x+BASE][y+BASE] = 1  # 通れない壁は1にする

    dist[BASE][BASE] = 0
    grid[BASE][BASE] = 1  # 既に通った箇所はもう通らないので1にする
    que = deque([(BASE,BASE)])
    while que:
        x, y = que.popleft()

        if (x, y) == (X, Y):
            print(dist[X][Y])
            return

        for nx, ny in ((x+1, y+1), (x, y+1), (x-1, y+1), (x+1, y), (x-1, y), (x, y-1)):
            if ny<0 or ny>500 or nx<0 or nx>500: continue
            if grid[nx][ny] == 1: continue
            grid[nx][ny] = 1
            dist[nx][ny] = dist[x][y] + 1
            que.append((nx, ny))

    print(-1)
    # print("−1")


if __name__ == "__main__":
    solve()
