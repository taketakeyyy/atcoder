# -*- coding:utf-8 -*-
from collections import defaultdict

def solve():
    # 番号を振り直す方法
    N = int(input())
    A = list(map(int, input().split()))
    # Aの番号を、出現順に振り直す
    remap = defaultdict(int)
    ni = 1
    for i, a in enumerate(A):
        if remap[a] == 0:
            remap[a] = ni
            ni += 1
        A[i] = remap[a]

    # Bも振り直す
    B = list(map(int, input().split()))
    for i, b in enumerate(B):
        if remap[b] == 0:
            remap[b] = ni
            ni += 1
        B[i] = remap[b]

    # dpA[i] := A[i]まで見てきたときの最大値
    dpA = [-1 for _ in range(N)]
    dpA[0] = A[0]
    for i in range(1, N):
        dpA[i] = max(dpA[i-1], A[i])

    # dpB[i] := B[i]まで見たときの(最大値, 集合の長さ)
    dpB = [(-1, -1) for _ in range(N)]
    dpB[0] = (B[0], 1)
    st = set()
    st.add(B[0])
    for i in range(1, N):
        st.add(B[i])
        dpB[i] = (max(dpB[i-1][0], B[i]), len(st))

    # クエリ処理
    Q = int(input())
    for _ in range(Q):
        x, y = list(map(int, input().split()))
        x -= 1
        y -= 1

        maxA = dpA[x]
        maxB = dpB[y][0]
        lensetB = dpB[y][1]
        if maxA==maxB and maxA==lensetB:
            print("Yes")
        else:
            print("No")


if __name__ == "__main__":
    solve()
