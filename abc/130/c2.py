# -*- coding:utf-8 -*-

def solve():
    W, H, x, y = list(map(int, input().split()))

    # 面積の大きくない方の最大値って面積の半分のことじゃね？
    area_ans = W*H/2

    # x,yが長方形の重心にあるなら無限の直線で分割できる(1)
    # そうでないなら、たった一本が存在する？

    if x==W/2 and y==H/2:
        is_sep = 1
    else:
        is_sep = 0
    
    print(area_ans, is_sep)


if __name__ == "__main__":
    solve()
