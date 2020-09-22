# -*- coding:utf-8 -*-

def solve():
    N, K, C = map(int, input().split())
    S = input()

    # 右詰めで働く日
    right = [None for _ in range(len(S))]
    day = K
    i = N
    while i > 0:
        i -= 1

        if S[i] == "x": continue
        right[i] = day
        day -= 1
        if day < 1: break
        i -= C

    # 左詰めで働く日
    left = [None for _ in range(len(S))]
    day = 1  # 働いた日数
    i = -1
    while i < N:
        i += 1

        if S[i] == "x": continue
        left[i] = day

        # 検証
        if left[i] == right[i]:
            print(i+1)

        day += 1
        if day > K: break
        i += C


if __name__ == "__main__":
    solve()
