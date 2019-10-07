# -*- coding:utf-8 -*-
import queue


def solve():
    R, C = list(map(int, input().split()))
    sy, sx = list(map(int, input().split()))
    gy, gx = list(map(int, input().split()))
    sy, sx = sy-1, sx-1
    gy, gx = gy-1, gx-1

    meiro = []
    for i in range(R):
        line = list(input())
        meiro.append(line)

    will_visit = queue.Queue()
    will_visit.put((sy, sx, 0))  # これから訪れる座標と移動したコスト(y, x, cost)

    visited = set()  # 到達済み
    visited.add((sy, sx))

    while True:
        ny, nx, ncost = will_visit.get()
        if ny == gy and nx == gx:
            print(ncost)
            return

        if meiro[ny-1][nx] != "#" and not (ny-1, nx) in visited:
            # 上方向に移動
            will_visit.put((ny-1, nx, ncost+1))
            visited.add((ny-1, nx))
        if meiro[ny+1][nx] != "#" and not (ny+1, nx) in visited:
            # 下方向に移動
            will_visit.put((ny+1, nx, ncost+1))
            visited.add((ny+1, nx))
        if meiro[ny][nx-1] != "#" and not (ny, nx-1) in visited:
            # 左方向に移動
            will_visit.put((ny, nx-1, ncost+1))
            visited.add((ny, nx-1))
        if meiro[ny][nx+1] != "#" and not (ny, nx+1) in visited:
            # 右方向に移動
            will_visit.put((ny, nx+1, ncost+1))
            visited.add((ny, nx+1))


if __name__ == "__main__":
    solve()
