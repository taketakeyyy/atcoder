# -*- coding:utf-8 -*-

if __name__ == "__main__":
    H, W = list(map(int, input().split()))
    # input
    xs = [[0 for w in range(W)] for h in range(H)]
    for h in range(H):
        a = list(map(int, input().split()))
        for w in range(W):
            xs[h][w] = a[w]

    # 戦略としては、右下にコインをうつしていく
    ops = []
    for h in range(H):
        for w in range(W):
            if xs[h][w]%2 != 0:
                # マスが奇数なら
                if w < W-1:
                    # 右にコインを移す
                    xs[h][w] -= 1
                    xs[h][w+1] += 1
                    ops.append("{} {} {} {}".format(h+1, w+1, h+1, w+1+1))
                elif w == W-1 and h != H-1:
                    # 下にコインを移す
                    xs[h][w] -= 1
                    xs[h+1][w] += 1
                    ops.append("{} {} {} {}".format(h+1, w+1, h+1+1, w+1))
    print(len(ops))
    for op in ops:
        print(op)
