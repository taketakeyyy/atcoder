# -*- coding:utf-8 -*-

def solve():
    N = input()
    A = list(map(int, input().split()))
    min_a = float("inf")
    max_a = 0
    for a in A:
        min_a = min(min_a, a)
        max_a = max(max_a, a)
    print(max_a - min_a)

if __name__ == "__main__":
    solve()
