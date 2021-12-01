# -*- coding:utf-8 -*-

def solve():
    N, K = map(int, list(input().split()))

    # 素因数列挙
    C = [0 for _ in range(N+1)]  # C[i] := 整数iが持つ素因数の数
    for i in range(2, N+1):
        if C[i] != 0: continue

        for j in range(i, N+1, i):
            C[j] += 1

    # 答えを計算
    # ans = sum(1 for c in C if c >= K)
    ans = 0
    for i in range(2, N+1):
        if C[i] >= K: ans += 1
    print(ans)


if __name__ == "__main__":
    solve()

