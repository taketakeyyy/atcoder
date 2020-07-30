# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    Ps = list(map(int, input().split()))
    Ps.sort()
    ans = sum(Ps[0:K])
    print(ans)


if __name__ == "__main__":
    solve()
