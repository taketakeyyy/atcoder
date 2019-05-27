# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    """考え方
    ruiseki[i] := i番目までの累積和

    ・ruiseki[0]を+にするパターン
    ・ruiseki[0]を-にするパターン

    の2通りを求め、小さい方を答えにする
    """

    # ruiseki[0]を+にするパターン
    ans1 = 0
    ruiseki = [0] * N
    ruiseki[0] = A[0]
    if ruiseki[0] <= 0:
        diff = abs(ruiseki[0] - 1)
        ans1 += diff
        ruiseki[0] = 1

    for i in range(1, N):
        ruiseki[i] = ruiseki[i-1] + A[i]

        if i%2 != 0:
            # iが奇数
            if ruiseki[i] >= 0:
                diff = abs(ruiseki[i] - (-1))
                ans1 += diff
                ruiseki[i] = -1
        else:
            # iが偶数
            if ruiseki[i] <= 0:
                diff = abs(ruiseki[i] - 1)
                ans1 += diff
                ruiseki[i] = 1
    
    # ruiseki[0]を-にするパターン
    ans2 = 0
    ruiseki = [0] * N
    ruiseki[0] = A[0]
    if ruiseki[0] >= 0:
        diff = abs(ruiseki[0] - (-1))
        ans2 += diff
        ruiseki[0] = -1

    for i in range(1, N):
        ruiseki[i] = ruiseki[i-1] + A[i]

        if i%2 != 0:
            # iが奇数
            if ruiseki[i] <= 0:
                diff = abs(ruiseki[i] - 1)
                ans2 += diff
                ruiseki[i] = 1
        else:
            # iが偶数
            if ruiseki[i] >= 0:
                diff = abs(ruiseki[i] - (-1))
                ans2 += diff
                ruiseki[i] = -1
    
    print(min(ans1, ans2))


if __name__ == "__main__":
    solve()
