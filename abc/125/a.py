# -*- coding:utf-8 -*-

def solve():
    A, B, T = list(map(int, input().split()))

    ans = (T//A)*B
    print(ans)

if __name__ == "__main__":
    solve()
