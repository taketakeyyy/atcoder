# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    total = 0 # 踏み台の高さ
    pre_a = As[0]
    for i in range(1, N):
        diff = pre_a - As[i]
        if diff > 0:
            # 前の人のほうが高い
            total += diff
            As[i] += diff
        else:
            # 後ろの人のほうが高い
            pass
        pre_a = As[i]

    print(total)


if __name__ == "__main__":
    solve()
