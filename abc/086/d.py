# -*- coding:utf-8 -*-

def solve():
    # TLS
    import numpy as np
    N, K = list(map(int, input().split()))
    grid = [[0 for _ in range(2*K)] for __ in range(K)]
    # grid = np.array(grid)

    for _ in range(N):
        x, y, c = input().split()
        x, y = int(x), int(y)
        # 全部Bに変換する
        if c == "W":
            x += K
        # x,yを[0,2K)の範囲に変換する
        x, y = x%(2*K), y%(2*K)
        # [(0,0), (K, 2K))の範囲に変換する。
        # (変換1) (x+K, y+K) -> (x, y)
        # (変換2) (x+K, y) -> (x, y+K)
        if x >= K and y >= K:
            x, y = x-K, y-K
        if x >= K:
            x, y = x-K, y+K
        grid[x][y] += 1  # 希望の位置を+1にする


    # 2次元累積和rを作る
    r = [[0 for _ in range(2*K+1)] for __ in range(K+1)]
    r[1][1] = grid[0][0]
    for x in range(1, K):
        r[x+1][1] = r[x][1] + grid[x][0]
    for y in range(1, 2*K):
        r[1][y+1] = r[1][y] + grid[0][y]

    for x in range(1, K):
        for y in range(1, 2*K):
            r[x+1][y+1] = r[x+1][y] + r[x][y+1] - r[x][y] + grid[x][y]


    def calc(x1, y1, x2, y2):
        """[(x1,y1), (x2,y2)]の範囲の累積和を返す"""
        return r[x2+1][y2+1] - r[x2+1][y1] - r[x1][y2+1] + r[x1][y1]

    # 答えを探索する
    ans = 0
    for x in range(K):
        for y in range(2*K):
            total = 0
            if y+K-1 >= 2*K and x+K-1 >= K:
                # xとyが境界をまたぐとき
                x1, y1 = x, y
                x2, y2 = K-1, 2*K-1
                total += calc(x1, y1, x2, y2)

                x3, y3 = x, 0
                x4, y4 = K-1, (y+K-1)%(2*K)
                total += calc(x3, y3, x4, y4)

                x5, y5 = 0, y4+1
                x6, y6 = x1-1, y1-1
                total += calc(x5, y5, x6, y6)

            elif y+K-1 >= 2*K:
                # yのみが境界をまたぐとき
                x1, y1 = 0, y
                x2, y2 = K-1, 2*K-1
                total += calc(x1, y1, x2, y2)

                x3, y3 = 0, 0
                x4, y4 = K-1, (y+K-1)%(2*K)
                total += calc(x3, y3, x4, y4)

            elif x+K-1 >= K:
                # xのみが境界をまたぐとき
                x1, y1 = x, y
                x2, y2 = K-1, y+K-1
                total += calc(x1, y1, x2, y2)

                if y2+1 < 2*K:
                    x3, y3 = 0, y2+1
                    x4, y4 = x-1, 2*K-1
                    total += calc(x3, y3, x4, y4)

                    x5, y5 = 0, 0
                    x6, y6 = x-1, y-1
                    total += calc(x5, y5, x6, y6)
                else:
                    x3, y3 = 0, y2+1
                    x4, y4 = x-1, 2*K-1
                    total += calc(x3, y3, x4, y4)
            else:
                # xもyもまたがないとき
                x1, y1 = x, y
                x2, y2 = x+K-1, y+K-1
                total += calc(x1, y1, x2, y2)
            ans = max(ans, total)
    print(ans)


if __name__ == "__main__":
    solve()
