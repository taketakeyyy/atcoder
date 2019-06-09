# -*- coding:utf-8 -*-

def solve():
    P, Q, R = list(map(int, input().split()))
    ans = min(P+Q, Q+R, R+P)

    print(ans)

if __name__ == "__main__":
    solve()
