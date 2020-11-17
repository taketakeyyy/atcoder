# -*- coding:utf-8 -*-

def solve():
    H, W, N, M = list(map(int, input().split()))
    lights = []
    block = [[0 for _ in range(W)] for __ in range(H)]  # 1:ブロック, 0:それ以外
    yoko = [[0 for _ in range(W)] for __ in range(H)]  # 1:照らせる, 0:照らせない
    tate = [[0 for _ in range(W)] for __ in range(H)]  # 1:照らせる, 0:照らせない

    for i in range(N):
        a, b = list(map(int, input().split()))
        a, b = a-1, b-1
        lights.append((a,b))
    for i in range(M):
        c, d = list(map(int, input().split()))
        c, d = c-1, d-1
        block[c][d] = 1

    for h, w in lights:
        # 横方向を埋める
        yoko[h][w] = 1
        nw = w - 1
        while nw >= 0:  # ここの処理はほぼO(1)
            if yoko[h][nw] or block[h][nw]:
                break
            yoko[h][nw] = 1
            nw -= 1
        nw = w + 1
        while nw < W:  # ここの処理はほぼO(1)
            if yoko[h][nw] or block[h][nw]:
                break
            yoko[h][nw] = 1
            nw += 1

        # 縦方向を埋める
        tate[h][w] = 1
        nh = h - 1
        while nh >= 0:  # ここの処理はほぼO(1)
            if tate[nh][w] or block[nh][w]:
                break
            tate[nh][w] = 1
            nh -= 1
        nh = h + 1
        while nh < H:  # ここの処理はほぼO(1)
            if tate[nh][w] or block[nh][w]:
                break
            tate[nh][w] = 1
            nh += 1

    ans = 0
    for h in range(H):
        for w in range(W):
            ans += 1 if yoko[h][w]==1 and tate[h][w]==1 else yoko[h][w] + tate[h][w]
    print(ans)


if __name__ == "__main__":
    solve()
