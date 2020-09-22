# -*- coding:utf-8 -*-

def solve():
    W, H, x, y = list(map(int, input().split()))
    ans_area = W*H/2
    if x == W/2 and y == H/2:
        can_separate = 1
    else:
        can_separate = 0
    print("{} {}".format(ans_area, can_separate))


if __name__ == "__main__":
    solve()
