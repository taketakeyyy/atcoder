# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    conds = []
    for i in range(M):
        A, B = list(map(int, input().split()))
        A-=1
        B-=1
        conds.append((A,B))
    K = int(input())
    men = []
    for i in range(K):
        C, D = list(map(int, input().split()))
        C-=1
        D-=1
        men.append((C,D))

    # 全探索
    ans = 0
    for bit in range(0, 2**K):
        balls = [0 for _ in range(N)]  # 皿iのぼーるの数
        for k in range(K):
            balls[men[k][(bit>>k)&1]] += 1

        total = 0
        for a, b in conds:
            if balls[a]>=1 and balls[b]>=1:
                total += 1
        ans = max(ans, total)

    print(ans)


if __name__ == "__main__":
    solve()
