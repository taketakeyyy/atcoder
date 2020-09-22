# -*- coding:utf-8 -*-

def determine_color(rate):
    if rate >= 1 and rate <= 399:
        return 0
    elif rate >= 400 and rate <= 799:
        return 1
    elif rate >= 800 and rate <= 1199:
        return 2
    elif rate >= 1200 and rate <= 1599:
        return 3
    elif rate >= 1600 and rate <= 1999:
        return 4
    elif rate >= 2000 and rate <= 2399:
        return 5
    elif rate >= 2400 and rate <= 2799:
        return 6
    elif rate >= 2800 and rate <= 3199:
        return 7
    else:
        return 8


def solve():
    N = int(input())
    A = list(map(int, input().split()))

    """方針
    色が8のとき、何色にもなれる。

    先に0~7の色を埋める(Trueにして)。これが最小の数。
    
    その後、最小の数に、色が8の数を足す。それが最大の数。

    問題文に書かれている色以外にもなれることに注意。黒色とか。
    """
    min_colors = [False] * 8
    color8_cnt = 0
    for i, a in enumerate(A):
        color = determine_color(a)
        if color == 8:
            color8_cnt += 1
            continue
        min_colors[color] = True
    
    min_ans = 0
    for i, c in enumerate(min_colors):
        if c:
            min_ans += 1
    
    max_ans = min_ans
    max_ans += color8_cnt

    if min_ans == 0 and color8_cnt != 0:
        min_ans = 1

    print("{} {}".format(min_ans, max_ans))



if __name__ == "__main__":
    solve()
