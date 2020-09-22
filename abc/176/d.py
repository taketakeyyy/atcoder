# -*- coding:utf-8 -*-

def solve():
    import sys
    from collections import deque
    import heapq

    H, W = list(map(int, sys.stdin.readline().split()))
    Ch, Cw = list(map(int, sys.stdin.readline().split()))
    Ch, Cw = Ch-1, Cw-1
    Dh, Dw = list(map(int, sys.stdin.readline().split()))
    Dh, Dw = Dh-1, Dw-1
    S = []
    for _ in range(H):
        s = input()
        S.append(list(s))

    que = []
    heapq.heapify(que)
    heapq.heappush(que, [0, Ch+Cw*(10**4)])  # [ワープ回数, 座標]
    visited = set()
    while len(que) != 0:
        n, yx = heapq.heappop(que)
        y, x = yx%(10**4), yx//(10**4)
        if (y, x) in visited: continue
        visited.add((y, x))

        # ゴールか？
        if y == Dh and x == Dw:
            print(n)
            return

        # 上下左右移動可能ならばqueに入れる
        for ny, nx in ([y-1, x], [y+1, x], [y, x-1], [y, x+1]):
            if 0 <= ny < H and 0 <= nx < W and not (ny, nx) in visited and S[ny][nx] == ".":
                heapq.heappush(que, [n, ny+nx*(10**4)])
        # ワープ可能位置をqueに入れる
        for ny, nx in ([y-2, x-2], [y-2, x-1], [y-2, x], [y-2, x+1], [y-2, x+2],
                       [y-1, x-2], [y-1, x-1], [y-1, x+1], [y-1, x+2],
                       [y, x-2], [y, x+2],
                       [y+2, x-2], [y+2, x-1], [y+2, x], [y+2, x+1], [y+2, x+2],
                       [y+1, x-2], [y+1, x-1], [y+1, x+1], [y+1, x+2]):
            if 0 <= ny < H and 0 <= nx < W and not (ny, nx) in visited and S[ny][nx] == ".":
                heapq.heappush(que, [n+1, ny+nx*(10**4)])

    # ゴールはたどり着かなかったよ・・・
    print(-1)
    return


def solve2():
    """TLE"""
    import sys
    from collections import deque
    import heapq

    H, W = list(map(int, sys.stdin.readline().split()))
    Ch, Cw = list(map(int, sys.stdin.readline().split()))
    Ch, Cw = Ch-1, Cw-1
    Dh, Dw = list(map(int, sys.stdin.readline().split()))
    Dh, Dw = Dh-1, Dw-1
    S = []
    for _ in range(H):
        s = input()
        S.append(list(s))

    que = []
    heapq.heapify(que)
    heapq.heappush(que, [0, Ch, Cw])  # [ワープ回数, h座標, w座標]
    visited = set()
    while len(que) != 0:
        n, y, x = heapq.heappop(que)
        visited.add((y, x))

        # ゴールか？
        if y == Dh and x == Dw:
            print(n)
            return

        # 上下左右移動可能ならばqueに入れる
        for ny, nx in ([y-1, x], [y+1, x], [y, x-1], [y, x+1]):
            if 0 <= ny < H and 0 <= nx < W and not (ny, nx) in visited and S[ny][nx] == ".":
                heapq.heappush(que, [n, ny, nx])
        # ワープ可能位置をqueに入れる
        for ny, nx in ([y-2, x-2], [y-2, x-1], [y-2, x], [y-2, x+1], [y-2, x+2],
                       [y-1, x-2], [y-1, x-1], [y-1, x+1], [y-1, x+2],
                       [y, x-2], [y, x+2],
                       [y+2, x-2], [y+2, x-1], [y+2, x], [y+2, x+1], [y+2, x+2],
                       [y+1, x-2], [y+1, x-1], [y+1, x+1], [y+1, x+2]):
            if 0 <= ny < H and 0 <= nx < W and not (ny, nx) in visited and S[ny][nx] == ".":
                heapq.heappush(que, [n+1, ny, nx])

    # ゴールはたどり着かなかったよ・・・
    print(-1)
    return


if __name__ == "__main__":
