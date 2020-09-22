# -*- coding:utf-8 -*-
"""考え方
解説動画をみてください

・以下のようなグラフを構築して解く
![d1](img/d1.jpg)

・適当なスタート箇所（図ではx1）の初期値を0にして、そこから隣接するxiの座標を計算していく
![d2](img/d2.jpg)

・計算した座標に矛盾があれば、"No"を出力する。矛盾がなければ、"Yes"を出力する。
![d3](img/d3.jpg)

"""
def solve():
    N, M = list(map(int, input().split()))
    MAX = 10**9
    L, R, D = [], [], []
    for i in range(M):
        _in = list(map(int, input().split()))
        L.append(_in[0])
        R.append(_in[1])
        D.append(_in[2])

    E = [{} for _ in range(N)]
    for i in range(M):
        E[L[i]-1][R[i]-1] = D[i]  # E[x1][x2] := x1からx2までの差
        E[R[i]-1][L[i]-1] = -D[i] # E[x2][x1] := x2からx1までの差
    
    V = [None] * N

    for i in range(N):
        if V[i] is not None:
            continue
        V[i] = 0
        q = [i]
        while q:
            j = q.pop()
            v = V[j]
            for k, d in E[j].items():
                if V[k] is None:
                    V[k] = v+d
                    q.append(k)
    ans = True
    for l, e in enumerate(E):
        for r, d in e.items():
            ans = ans and V[r]-V[l] == d
        if not ans:
            break
    print("Yes" if ans else "No")
        

if __name__ == "__main__":
    solve()
