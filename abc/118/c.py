"""解説 動画URL：https://www.youtube.com/watch?v=qBxvXX5hkAA
ユークリッドの互除法

モンスターの体力が1にならない場合を考えてみる。

モンスターの体力： 12  20  16
                  ↓   ↓   ↓
                  0   4   0

4は作れる。1~3は作れるか？作れない。なぜか？

12 = 4*3
20 = 4*5
16 = 4*4
x  = 4*(a-b)

xの最小値は、(a-b)=1のときで、x=4

よって、最大公約数より小さくはならないので、最大公約数が答え。

"""

def gcd(a, b):
    """ 最大公約数。aはbより大きいこと """
    if b == 0:
        return a
    else:
        return gcd(b, a%b)


def solve():
    N = int(input())
    A = [int(x) for x in input().split(" ")]

    A.sort(reverse=True)
    ans = A[0]
    for i in range(1, N):
        ans = gcd(ans, A[i])

    print(ans)


if __name__ == "__main__":
    solve()