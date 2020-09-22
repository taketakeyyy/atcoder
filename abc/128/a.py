# -*- coding:utf-8 -*-

def solve():
    A, P = list(map(int, input().split()))
    sum_kakera  = A*3 + P

    ans = sum_kakera // 2

    print(ans)

if __name__ == "__main__":
    solve()
