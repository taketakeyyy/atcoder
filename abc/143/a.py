# -*- coding:utf-8 -*-

def solve():
    A, B = list(map(int, input().split()))
    ans = max(0, A-B*2)
    print(ans)

if __name__ == "__main__":
    solve()
