# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    max_add = -float("inf")
    min_add = float("inf")
    max_sub = -float("inf")
    min_sub = -float("inf")
    for i in range(N):
        x, y = list(map(int, input().split()))
        if x+y > max_add:
            max_add = x+y
            max_add_x, max_add_y = x, y
        if x+y < min_add:
            min_add = x+y
            min_add_x, min_add_y = x, y
        if x-y > max_sub:
            max_sub = x-y
            max_sub_x, max_sub_y = x, y
        if y-x > min_sub:
            min_sub = y-x
            min_sub_x, min_sub_y = x, y

    print(max(abs(max_add_x-min_add_x)+abs(max_add_y-min_add_y), abs(max_sub_x-min_sub_x)+abs(max_sub_y-min_sub_y)))


if __name__ == "__main__":
    solve()
