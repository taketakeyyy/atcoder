# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    # 累積和で解く
    # ruiseki[i] := i番目までの累積和(0 <= i <= N-1)
    ruiseki = [0] * N
    ruiseki[0] = A[0]
    for i in range(1, N):
        ruiseki[i] = ruiseki[i-1] + A[i]
    
    min_diff = float("inf") # xとyの最小差
    for i in range(0, N-1):
        x = ruiseki[i]
        y = ruiseki[N-1] - ruiseki[i]
        min_diff = min(min_diff, abs(x-y))
    
    print(min_diff)

if __name__ == "__main__":
    solve()
