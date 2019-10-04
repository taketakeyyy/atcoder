#-*- coding:utf-8 -*-
import math

if __name__ == "__main__":
    """
    操作1：２つを選んで、その両方を+1する
    操作2：１つを選んで、その数字を+2する
    """
    nums = list(map(int, input().split()))
    # (1) 2番目に大きい数字が、最も大きい数字になるように、操作1を繰り返す
    # (2) その後、最も小さい数字が、最も大きい数字に鳴るように操作2を繰り返す

    # (1)
    nums.sort()
    A = nums[0]
    B = nums[1]
    C = nums[2]
    ans = 0
    n = C - B # 操作回数
    A += n
    B += n
    ans += n

    # (2)
    diff = C - A
    if diff%2 != 0:
        C += 1
        B += 1
        ans += 1 # 最も大きい数字に追加で操作1を行う
    diff = C - A
    ans += math.floor(diff/2)
    print(ans)
