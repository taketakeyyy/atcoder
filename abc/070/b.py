# -*- coding:utf-8 -*-

def solve():
    A, B, C, D = list(map(int, input().split()))
    start = max(A, C)
    end = min(B, D)

    ans = max(end-start, 0)
    print(ans)

if __name__ == "__main__":
    solve()
