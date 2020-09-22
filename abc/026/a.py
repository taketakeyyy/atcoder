# -*- coding:utf-8 -*-

def solve():
    A = int(input())
    x = 1
    y = A-1

    ans = 0
    while x <= y:
        ans = max(ans, x*y)
        x += 1
        y -= 1

    print(ans)


if __name__ == "__main__":
    solve()
