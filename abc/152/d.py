# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    C = [[0 for _ in range(10)] for __ in range(10)]  # C[i][j] := 左端がi,右端がjの整数の個数

    def check(n):
        r = n%10
        if r == 0:
            return None
        while (n//10)!=0:
            n = n//10
        l = n
        return l, r

    for i in range(1, N+1):
        lr = check(i)
        if lr is None: continue
        l, r = lr
        C[l][r] += 1

    # 答えを計算する
    ans = 0
    for i in range(1, 10):
        for j in range(1, 10):
            ans += C[i][j] * C[j][i]
    print(ans)


if __name__ == "__main__":
    solve()
