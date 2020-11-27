# -*- coding:utf-8 -*-

def solve():
    import numpy as np

    H, W, M = list(map(int, input().split()))
    yoko = np.array([0 for _ in range(H)])  # hに爆弾を置いたとき、横方向にいくつ爆破対象を爆破できるか
    tate = np.array([0 for _ in range(W)])  # wに爆弾を置いたとき、縦方向にいくつ爆破対象を爆破できるか
    targets = set()  # 爆破対象の集合

    for _ in range(M):
        h, w = list(map(int, input().split()))
        yoko[h-1] += 1
        tate[w-1] += 1
        targets.add((h-1, w-1))

    yoko_max = yoko.max()
    tate_max = tate.max()

    yoko_cands = np.where(yoko==yoko_max)[0]
    tate_cands = np.where(tate==tate_max)[0]

    # HxWのように見えるが、爆破対象はたかだかMなので、O(M)
    is_found = False
    for h in yoko_cands:
        for w in tate_cands:
            if not (h, w) in targets:  # 爆破対象の座標じゃないほうが、一個多く爆破できる
                is_found = True
                break
        if is_found:
            break

    if is_found:
        print(tate_max+yoko_max)
    else:
        print(tate_max+yoko_max-1)

if __name__ == "__main__":
    solve()
