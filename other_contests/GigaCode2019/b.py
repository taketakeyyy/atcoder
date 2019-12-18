# -*- coding:utf-8 -*-

def solve():
    N,X,Y,Z = map(int, input().split())
    ans = 0
    for _ in range(N):
        A, B = map(int, input().split())
        if (A >= X and B >= Y) and (A+B >= Z):
            ans += 1
    print(ans)

if __name__ == "__main__":
    solve()
