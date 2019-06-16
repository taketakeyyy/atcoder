# -*- coding:utf-8 -*-
"""考え方
よくわからんけど、縦か横の直線で分割する？
あと原点から(x,y)座標へ向けて斜めに分割する奴も考える

"""
def solve():
    W, H, x, y = list(map(int, input().split()))

    # 縦に分割する場合
    ans1 = min(x*H, (W-x)*H)

    # 横に分割する場合
    ans2 = min(W*y, W*(H-y))

    # 斜めに分割する場合
    ans3 = -1
    if x != 0 and y != 0:
        d = y/x
        if d <= 1:
            # 傾きが1以下の場合
            ans3 = W * (W*d) / 2
        else:
            # 傾きが1より大きい
            d = x/y
            ans3 = H * (H*d) / 2

    ans = max(ans1, ans2, ans3)

    if ((ans==ans1 and ans1==ans2) or 
       (ans==ans2 and ans2==ans3) or 
       (ans==ans3 and ans3==ans1)):
        is_multi = 1
    else:
        is_multi = 0

    print(ans, is_multi)


if __name__ == "__main__":
    solve()
