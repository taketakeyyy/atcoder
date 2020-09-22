# -*- coding:utf-8 -*-

def solve():
    import numpy as np
    import copy

    H, W, K = list(map(int, input().split()))
    Cs = []
    for _ in range(H):
        s = input()
        lst = []
        for moji in s:
            a = 0 if moji == "." else 1
            lst.append(a)
        Cs.append(lst)
    Cs = np.array(Cs)

    Hs = []
    for bits in range(1<<H):
        lst = []
        for i in range(H):
            lst.append(bits>>i&1)
        Hs.append(np.array(lst).reshape(H,1))

    Ws = []
    for bits in range(1<<W):
        lst = []
        for i in range(W):
            lst.append(bits>>i&1)
        Ws.append(np.array(lst))

    ans = 0
    oCs = Cs
    for hs in Hs:
        for ws in Ws:
            Cs = copy.deepcopy(oCs)
            Cs *= ws
            Cs *= hs
            if Cs.sum() == K:
                ans += 1
    print(ans)


if __name__ == "__main__":
    solve()
