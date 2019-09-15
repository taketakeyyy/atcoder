# -*- coding:utf-8 -*-

"""解法
+と*しかないのがミソで、

つまりすべての項が0になる必要がある。ちなみに項とは、

a*b + c*d*e + f

でいうa*b, c*d*e, fのことで、+演算子で区切られたものである。

"""

def solve():
    S = input()
    kous = S.split("+")

    # 各項について、0が含まれているならば、その項は0になる。
    ans = 0
    for kou in kous:
        if "0" in kou:
            continue

        # kou = "1*2*3*9" みたいなときが0にならないパターンで、その場合は数字をどれかひとつ0に書き換えればよい
        ans += 1

    print(ans)



if __name__ == "__main__":
    solve()
