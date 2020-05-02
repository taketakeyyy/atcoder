# -*- coding:utf-8 -*-

def solve():
    X = int(input())
    a = 100

    ans = 0
    if a >= X:
        print(ans)
        return

    while True:
        a += int(a*0.01)
        ans += 1
        if a >= X:
            print(ans)
            return

if __name__ == "__main__":
    solve()
