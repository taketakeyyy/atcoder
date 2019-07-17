# -*- coding:utf-8 -*-
import numpy as np

def solve():
    H, W = list(map(int, input().split()))
    S = []
    for i in range(H):
        S.append(list(input()))
    grid = (np.array(S) == ".") * 1  # ランプをおける:1, 障害物:0

    L = np.zeros((H,W), dtype=int)
    R = np.zeros((H,W), dtype=int)
    U = np.zeros((H,W), dtype=int)
    D = np.zeros((H,W), dtype=int)

    for j in range(W):
        if j==0:
            L[:,j] = grid[:,j]
        else:
            L[:,j] = (L[:,j-1]+1) * grid[:,j]
    
    for j in range(W-1, -1, -1):
        if j==(W-1):
            R[:,j] = grid[:,j]
        else:
            R[:,j] = (R[:,j+1] + 1) * grid[:, j]
    
    for i in range(H):
        if i==0:
            U[i,:] = grid[i,:]
        else:
            U[i,:] = (U[i-1,:]+1)*grid[i,:]
    
    for i in range(H-1, -1, -1):
        if i==(H-1):
            D[i,:] = grid[i,:]
        else:
            D[i,:] = (D[i+1,:]+1)*grid[i,:]
    
    ans = np.max(L+R+U+D-3)
    print(ans)

if __name__ == "__main__":
    solve()
