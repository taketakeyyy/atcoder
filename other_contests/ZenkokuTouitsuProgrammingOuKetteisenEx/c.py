# -*- coding:utf-8 -*-

def solve2():
    """整数 M を 11 で割った余りは、M の下から奇数桁目の数の和 から M の下から偶数桁目の数の和 を引いた値を 11で割った余りと一致します。"""
    N = int(input())

    # 偶数桁目の和を計算する
    odd_sum = 0
    i = 1  # 1始まり
    M = N
    while M != 0:
        if i%2 == 0:
            i += 1
            M //= 10
            continue
        odd_sum += M%10
        i += 1
        M //=10

    # 偶数桁目の和を計算する
    even_sum = 0
    i = 1
    M = N
    while M != 0:
        if i%2 == 0:
            even_sum += M%10
            i += 1
            M //=10
            continue
        i += 1
        M //= 10

    ans = (odd_sum - even_sum)%11
    print(ans)


def solve():
    N = int(input())
    print(N%11)

if __name__ == "__main__":
    solve2()
