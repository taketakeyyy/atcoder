# -*- coding:utf-8 -*-
"""考え方
(x, y)と長方形の中心を両方通るような直線で分割すると、大きくない方の面積は全体の半分の面積。

・与えられた(x, y)が長方形の中心の場合、区切り方は無限にある。
・与えられた(x, y)が長方形の中心でない場合、一通りに求まる。
"""
def solve():
    W, H, x, y = list(map(int, input().split()))

    ans_area = W*H/2

    if x == W/2 and y == H/2:
        is_multi = 1
    else:
        is_multi = 0
    
    print(ans_area, is_multi)

if __name__ == "__main__":
    solve()
