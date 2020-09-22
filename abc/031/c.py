# -*- coding:utf-8 -*-
import sys

"""解説

整数列をAsとして、偶数番号の累積和と、奇数番号の累積和を合体した数列dpをあらかじめ計算します

入力例２で考えます。

 i:  0  1  2  3  4  5
---------------------
As:  1 -3  3  9  1  6
dp:  1 -3  4  6  5 12

dp[4]には、As[0], As[2], As[4] の累積和が格納されています。
dp[5]には、As[1], As[3], As[5] の累積和が格納されています。

・たとえば高橋が1番(left), 青木が3番(right)を選んだときの数列Tsは、

 i:  0  1  2  3  4  5
---------------------
As:  1 -3  3  9  1  6
dp:  1 -3  4  6  5 12
Ts:    -3  3  9

となり、このときの青木の得点は3ですが、これはあらかじめ計算したdpを使えば、

青木の得点：dp[right-1] - dp[left-1] = 3
高橋の得点：dp[right] = 6

になります。


・たとえば高橋が5番(right), 青木が2番(left)を選んだときの数列Tsは、

 i:  0  1  2  3  4  5
---------------------
As:  1 -3  3  9  1  6
dp:  1 -3  4  6  5 12
Ts:        3  9  1  6

となり、このときの青木の得点は15ですが、これはあらかじめ計算したdpを使って、

青木の得点：dp[right] - dp[left-1] = 15
高橋の得点：dp[right-1] - dp[left-2] = 4

になります。


このように、累積和を使って高橋と青木の得点計算を高速でおこなうことができるようになります。

あとは全探索で、青木の得点が最大値のときの、高橋の得点を計算していき、高橋の得点の最大値を算出します。

"""

def solve():
    N = int(input())
    As = list(map(int, sys.stdin.readline().split()))

    if N == 2:
        print(As[0])
        return

    # 累積和(dp?)
    dp = [0]*N
    dp[0] = As[0]
    dp[1] = As[1]
    for i in range(2, N):
        dp[i] = dp[i-2] + As[i]

    # 全探索
    # i := 高橋が選んだ番号
    # j := 青木が選んだ番号
    ans = -float("inf")
    for i in range(0, N):
        aoki_max = -float("inf")  # 青木の最大の得点
        aoki_max_j = None         # 青木の最大の得点のときの番号
        for j in range(0, N):
            # 青木が最も多く得点を得られるときの j(aoki_max_j) を決める
            if i == j: continue
            left, right = min(i,j), max(i,j)

            if (right-left)%2 == 0:
                if left-1 >= 0:
                    aoki = dp[right-1] - dp[left-1]
                else:
                    aoki = dp[right-1]
            else:
                if left-1 >= 0:
                    aoki = dp[right] - dp[left-1]
                else:
                    aoki = dp[right]
            
            if aoki > aoki_max:
                aoki_max = max(aoki_max, aoki)
                aoki_max_j = j
        
        # 青木が aoki_max_j を選んだときの高橋の点数を計算する
        left, right = min(i, aoki_max_j), max(i, aoki_max_j)
        
        if (right-left)%2 == 0:
            if left-2 >= 0:
                takahashi = dp[right] - dp[left-2]
            else:
                takahashi = dp[right]
        else:
            if left-2 >= 0:
                takahashi = dp[right-1] - dp[left-2]
            else:
                takahashi = dp[right-1]

        # 高橋が得られる得点として考えられる最大値を更新する
        ans = max(ans, takahashi)

    print(ans)
            

if __name__ == "__main__":
    solve()
