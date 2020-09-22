# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    W = list(map(int, input().split()))

    ans = float("inf")
    for t in range(1, N):
        t_low_sum = sum(W[:t])
        t_up_sum = sum(W[t:])
        ans = min(ans, abs(t_low_sum-t_up_sum))
    
    print(ans)
        


if __name__ == "__main__":
    solve()
