# -*- coding:utf-8 -*-

def solve():
    N, D = list(map(int, input().split()))

    ans = 0
    for i in range(N):
        x, y = list(map(int, input().split()))
        d = (x**2+y**2)**(1/2)
        if d <= D:
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
