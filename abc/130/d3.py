# -*- coding:utf-8 -*-
import sys

"""しゃくとり法
 K = 10
 6 1 2 7 10 1 2 1


 6 1 2 7 10 1 2 1
|_|
 6

##
 6 1 2 7 10 1 2 1
|___|
  7

##
 6 1 2 7 10 1 2 1
|_____|
   9

##
 6 1 2 7 10 1 2 1
|_______|
    16

ans += N - right

## total < K になるまで、leftを右に1進める
 6 1 2 7 10 1 2 1
  |_____|
    10

ans += N - right

## total < K になるまで、leftを右に1進める
 6 1 2 7 10 1 2 1
    |___|
      9

## rightを右に1進める
 6 1 2 7 10 1 2 1
    |______|
       19

ans += N - right

## total < K になるまで、leftを右に1進める
 6 1 2 7 10 1 2 1
      |____|
        17

ans += N - right

## total < K になるまで、leftを右に1進める
 6 1 2 7 10 1 2 1
        |__|
         10

ans += N - right

## total < K になるまで、leftを右に1進める
 6 1 2 7 10 1 2 1
           |
           0


## rightを右に1進める
 6 1 2 7 10 1 2 1
           |_|
            1

## rightを右に1進める
 6 1 2 7 10 1 2 1
           |___|
             3

## rightを右に1進める
 6 1 2 7 10 1 2 1
           |_____|
              4

rightはこれ以上右に進めないので終了




"""

def solve():
    N, K = list(map(int, input().split()))
    As = list(map(int, sys.stdin.readline().split()))

    left = 0
    total = 0
    ans = 0
    for right in range(0, N):
        total += As[right]
        while total >= K:
            ans += N - right
            total -= As[left]
            left += 1

    print(ans)


if __name__ == "__main__":
    solve()
