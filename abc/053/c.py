# -*- coding:utf-8 -*-

def solve():
    x = int(input())

    """
    x点以上になる最小操作回数。初期状態は自由。
    6と5を交互に繰り返すだけで良くない？

    計算量はO(1)
    """

    # 6と5を何回繰り返せばよいか？
    ans = (x//11) * 2
    restX = x%11

    # 上面を6にする
    if restX > 0:
        restX -= 6
        ans += 1

    # 上面を5にする
    if restX > 0:
        ans += 1
    
    print(ans)


if __name__ == "__main__":
    solve()
