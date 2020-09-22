# -*- coding:utf-8 -*-

def solve():
    import sys
    import numpy as np

    N, M, X = list(map(int, sys.stdin.readline().split()))
    Cs = []
    AAs = []
    for _ in range(N):
        _in = list(map(int, sys.stdin.readline().split()))
        c, As = _in[0], _in[1:]
        Cs.append(c)
        AAs.append(np.array(As))

    ans = float("inf")
    for bit in range(2**N):
        total = 0
        masters = np.array([0]*M)

        for i in range(N):
            if bit>>i&1:
                total += Cs[i]
                masters += AAs[i]

            if sum(masters>=X) == M:
                ans = min(ans, total)

    if ans == float("inf"):
        print(-1)
    else:
        print(ans)


if __name__ == "__main__":
    solve()
