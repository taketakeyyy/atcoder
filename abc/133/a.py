# -*- coding:utf-8 -*-

def solve():
    N, A, B = list(map(int, input().split()))
    ans = min(N*A, B)
    print(ans)

if __name__ == "__main__":
    solve()
