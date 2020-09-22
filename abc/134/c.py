# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = []
    max1_num, max2_num = 0, 0
    for i in range(N):
        a = int(input())
        A.append(a)

        if a >= max1_num:
            max1_num, max2_num = a, max1_num
        elif a > max2_num:
            max2_num = a

    """方針
    最大値と、2番めに大きい値を覚えておく。
    除く値が最大値のとき、答えは2番めに大きい値。それ以外は最大値が答え。
    """

    for a in A:
        if a == max1_num:
            print(max2_num)
        else:
            print(max1_num)


if __name__ == "__main__":
    solve()
