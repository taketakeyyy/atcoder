# -*- coding:utf-8 -*-

def solve():
    import sys

    nums = list(map(int, sys.stdin.readline().split()))
    nums.sort(reverse=True)
    print(nums[2])

if __name__ == "__main__":
    solve()
