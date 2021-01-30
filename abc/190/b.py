# -*- coding:utf-8 -*-

def solve():
    N, S, D = list(map(int, input().split()))
    for _ in range(N):
        X, Y = list(map(int, input().split()))
        if X >= S or Y <= D:
            continue
        print("Yes")
        return
    print("No")

if __name__ == "__main__":
    solve()
