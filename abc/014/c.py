# -*- coding:utf-8 -*-

def solve():
    # いもす法
    N = int(input())
    NN = 1000002

    # (1) 加算処理
    imos = [0] * NN
    for i in range(N):
        a, b = list(map(int, input().split()))
        imos[a] += 1
        imos[b+1] -= 1

    # (2) 累積和処理
    for i in range(1, NN):
        imos[i] = imos[i] + imos[i-1]

    print(max(imos))


if __name__ == "__main__":
    solve()
