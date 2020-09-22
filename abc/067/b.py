# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    L = list(map(int, input().split()))
    L.sort(reverse=True)

    # 長いものからK本選べばよい
    ans = sum(L[0:K])
    print(ans)

if __name__ == "__main__":
    solve()
