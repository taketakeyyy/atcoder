#-*- coding:utf-8 -*-
import math

if __name__ == "__main__":
    N, A, B = list(map(int, input().split()))
    ans = 0
    for i in range(N, 0, -1):
        # 各桁の数をnumsに入れる
        nums = []
        num = i
        while 1:
            nums.append(num%10)
            num = int(math.floor(num/10))
            if num == 0:
                break
        # 各桁の和を求める
        sum_num = 0
        for num in nums:
            sum_num += num
        # 各桁の和がA以上B以下かを判定する
        if sum_num >= A and sum_num <= B:
            ans += i
    print(ans)
