# -*- coding:utf-8 -*-

def solve():
    A, B = input().split()

    # 2進浮動小数点数(float)にしたら誤差が発生するので、整数のまま計算する
    A = int(A)
    B = int(B.replace(".", ""))

    ans = A*B//100
    print(ans)


def solve2():
    A, B = input().split()

    # 10進小数が扱えるdecimalモジュールを使う
    from decimal import Decimal
    A = int(A)
    B = Decimal(B)

    ans = (A*B)//1
    print(ans)


if __name__ == "__main__":
    solve()
