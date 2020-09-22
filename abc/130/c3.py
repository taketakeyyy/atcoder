# -*- coding:utf-8 -*-

def solve():
    W, H, x, y = list(map(int, input().split()))
    ans = W*H/2
    is_separate = 0
    if x==W/2 and y==H/2:
        is_separate = 1
    print(ans, is_separate)


if __name__ == "__main__":
    solve()
