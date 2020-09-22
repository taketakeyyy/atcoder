# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    L, R, D = [], [], []
    for _ in range(M):
        l,r,d = list(map(int, input().split()))
        L.append(l)
        R.append(r)
        D.append(d)

    E = [{} for _ in range(M)]
    
    for l, r, d in zip(L, R, D):
        E[l-1][r-1] = d  # E[x1][x2] := x1からx2までの差がd
    
    V = [None]*N # V[xi] := xiの位置

    for i in range(N):
        V[i] = 0
        q = [i]
        while q:
            j = q.pop()
            for k, d in E[j].items():
                if V[k] is None:
                    # まだ座標が定まっていないなら
                    V[k] = V[j]+d
                    q.append(k)

if __name__ == "__main__":
    solve()
