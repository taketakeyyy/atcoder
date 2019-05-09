# -*- coding:utf-8 -*-

def solve():
    H, W = list(map(int, input().split()))
    S = [None] * H

    for i in range(H):
        S[i] = input()
    
    ans = [["#" for w in range(W)] for h in range(H)]
    for h in range(H):
        for w in range(W):
            if S[h][w] == ".":
                bomb = 0
                if w-1 >= 0 and h-1 >= 0:
                    if S[h-1][w-1] == "#":
                        bomb += 1
                if h-1 >= 0:
                    if S[h-1][w] == "#":
                        bomb += 1
                if h-1 >= 0 and w+1 < W:
                    if S[h-1][w+1] == "#":
                        bomb += 1
                if w-1 >= 0:
                    if S[h][w-1] == "#":
                        bomb += 1
                if w+1 < W:
                    if S[h][w+1] == "#":
                        bomb += 1
                if h+1 < H and w-1 >= 0:
                    if S[h+1][w-1] == "#":
                        bomb += 1
                if h+1 < H:
                    if S[h+1][w] == "#":
                        bomb += 1
                if h+1 < H and w+1 < W:
                    if S[h+1][w+1] == "#":
                        bomb += 1
                ans[h][w] = bomb
    
    for h in range(H):
        for w in range(W):
            print(ans[h][w], end="")
        print()

if __name__ == "__main__":
    solve()
