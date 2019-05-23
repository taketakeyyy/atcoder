# -*- coding:utf-8 -*-

""" 方針
[入力例１]
3 4
1 1
2 2
3 3

ans = [1, 2, 2, 3, 3, 3]
K=4より、答えは3

[考え方]
num_cnt_hash[num] := 数字numが配列に何個入っているか

"""

def solve():
    N, K = list(map(int, input().split()))
    A, B = [], []

    num_cnt_hash = {}
    for i in range(N):
        a, b = list(map(int, input().split()))

        if not a in num_cnt_hash:
            num_cnt_hash[a] = 0
        num_cnt_hash[a] += b
    
    nums = list(num_cnt_hash.keys())
    nums.sort()

    k = 0
    for num in nums:
        k += num_cnt_hash[num]
        if k >= K:
            print(num)
            return


if __name__ == "__main__":
    solve()
