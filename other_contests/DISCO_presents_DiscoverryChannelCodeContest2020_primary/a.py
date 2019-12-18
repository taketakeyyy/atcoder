# -*- coding:utf-8 -*-

def get_syokin(a):
    if a == 3:
        return 100000
    elif a == 2:
        return 200000
    elif a == 1:
        return 300000
    return 0

def solve():
    X, Y = map(int, input().split())
    ans = 0

    ans += get_syokin(X)
    ans += get_syokin(Y)

    if X==1 and Y==1:
        ans += 400000

    print(ans)


if __name__ == "__main__":
    solve()
