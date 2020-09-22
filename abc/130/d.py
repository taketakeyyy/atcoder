# -*- coding:utf-8 -*-
"""考え方
しゃくとり法
"""

def solve():
    N, K = list(map(int, input().split()))
    A = list(map(int, input().split()))

    ans = 0
    total = 0
    for r in range(N):
        total += A[r]
        if total >= K:
            ans += N - r  # こっから右側の部分文字列はすべてKを超えるので
            break

    # ここからしゃくとり法
    for l in range(1, N):
        total -= A[l-1]  # 左端を1個削除

        for i in range(r, N):
            if i != r:
                total += A[i]  # 右端を1個足す
            if total >= K:
                ans += N - i  # こっから右側の部分文字列はすべてKを超える
                break
        r = i  # 右端の更新

    print(ans)


if __name__ == "__main__":
    solve()
