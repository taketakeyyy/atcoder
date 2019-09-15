# -*- coding:utf-8 -*-
import sys

"""解説
 K = 6
 4 3 1 1 2 2 1 1 1 2
という数列を考える。

 4 3 1 1 2 2 1 1 1 2
|_|
 4

 4 3 1 1 2 2 1 1 1 2
|___|
  12
Kを超えたので、左端の4で割ったあと、左端の位置を1すすめる

 4 3 1 1 2 2 1 1 1 2
  |_|
   3

 4 3 1 1 2 2 1 1 1 2
  |_______|
      6

 4 3 1 1 2 2 1 1 1 2
  |_________|
       12
Kを超えたので、左端の3で割ったあと、左端の位置を1すすめる

 4 3 1 1 2 2 1 1 1 2
    |_____________|
          4

 4 3 1 1 2 2 1 1 1 2
    |_______________|
           8
Kを超えたので、左端の1で割ったあと、左端の位置を1すすめる

 4 3 1 1 2 2 1 1 1 2
      |_____________|
             8
まだKを超えてるので、左端の1で割ったあと、左端の位置を1すすめる

 4 3 1 1 2 2 1 1 1 2
        |___________|
             8
まだKを超えてるので、左端の2で割ったあと、左端の位置を1すすめる

 4 3 1 1 2 2 1 1 1 2
          |_________|
               4

よって答えは7

[上の入力例]
10 6
4
3
1
1
2
2
1
1
1
2

"""

def solve():
    N, K = list(map(int, sys.stdin.readline().split()))
    Ss = []
    for _ in range(N):
        s = int(input())
        Ss.append(s)

    if K == 0:
        # コーナーケース
        if 0 in Ss:
            print(N)
        else:
            print(0)
        return

    left = 0   # 左端
    ans = 0    # 最終的に出力する答え
    accum = 1  # 累積
    for right in range(N):
        accum *= Ss[right]

        if accum == 0:
            # 0を掛けた場合は例外で、Nを出力して終了
            print(N)
            return

        while accum > K:
            accum //= Ss[left]
            left += 1
        ans = max(ans, right-left+1)
    
    print(ans)


if __name__ == "__main__":
    solve()
