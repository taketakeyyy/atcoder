# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    start = []
    for i in range(N):
        a, b = list(map(int, input().split()))
        start.append((a, b))
    
    checkpoints = []
    for i in range(M):
        c, d = list(map(int, input().split()))
        checkpoints.append((c, d))
    
    # 1 <= N,M <= 50 なので、全探索しても高々 N*M = 2500

    for i in range(N):
        min_d = float("inf")
        for j in range(M):
            d = abs(start[i][0]-checkpoints[j][0]) + abs(start[i][1]-checkpoints[j][1])
            if d < min_d:
                min_d = d
                ans = j + 1
        print(ans)


if __name__ == "__main__":
    solve()
