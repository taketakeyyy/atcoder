# -*- coding:utf-8 -*-

def solve():
    X, Y, Z = list(map(int, input().split()))

    X = X - Z
    ans = int(X/(Y+Z))

    print(ans)


if __name__ == "__main__":
    solve()
