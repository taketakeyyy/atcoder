# -*- coding:utf-8 -*-
"""
いもす法で解く
解説：https://www.slideshare.net/chokudai/abc035

・やることは加算、構築、取得の3つの処理

・加算処理では
  -   l 番目の値にv加算する
  - r+1 番目の値に-v加算する

・構築処理
  - i番目の値を i+1 番目の値に加算する（累積和をする）

・取得処理
  - すると、各位置の値がそれぞれ求まる

【例】
・初期状態
i | 1  2  3  4  5  6  7
v | 0  0  0  0  0  0  0

・[2, 4]に2を加算
i | 1  2  3  4  5  6  7
v | 0  2  0  0 -2  0  0

・[4, 4]に3を加算
i | 1  2  3  4  5  6  7
v | 0  2  0  3 -5  0  0

・[1, 6]に1を加算
i | 1  2  3  4  5  6  7
v | 1  2  0  3 -5  0 -1

・累積和をする
i | 1  2  3  4  5  6  7
v | 1  3  3  6  1  1  0


 
"""
def solve():
    # いもす法で解く。計算量はO(N+Q)
    N, Q = list(map(int, input().split()))
    s = [0] * (N+1)

    # いもす法の加算処理
    for _ in range(Q):
        l, r = list(map(int, input().split()))
        s[l] += 1
        if r+1 != N+1:
            s[r+1] -= 1
    
    # いもす法の累積和（構築処理）
    ruiseki = [0] * (N+1)
    for i in range(1, N+1):
        ruiseki[i] += ruiseki[i-1] + s[i]
        if ruiseki[i]%2 == 0:
            ruiseki[i] = 0
        else:
            ruiseki[i] = 1
    
    # 答えを出力
    ans = "".join(list(map(str, ruiseki[1:])))
    print(ans)


if __name__ == "__main__":
    solve()
