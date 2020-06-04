# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))
    MAX = 10**18

    if 0 in As:
        print(0)
        return

    ans = 1
    for a in As:
        ans *= a
        if ans > MAX:
            print(-1)
            return
    print(ans)


if __name__ == "__main__":
    solve()
