# -*- coding:utf-8 -*-
import sys

def solve():
    nums = list(map(int, sys.stdin.readline().split()))
    sums = []
    N = len(nums)

    for i in range(N):
        for j in range(i+1, N):
            for k in range(j+1, N):
                sums.append(nums[i]+nums[j]+nums[k])

    sums.sort(reverse=True)
    print(sums[2])

if __name__ == "__main__":
    solve()
