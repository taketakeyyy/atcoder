# -*- coding:utf-8 -*-

def solve():
    N, X = list(map(int, input().split()))
    total = 0
    for i in range(N):
        v, p = list(map(int, input().split()))
        total += v*p
        if total > X*100:
            print(i+1)
            return
    print(-1)


if __name__ == "__main__":
    solve()
