# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    ans = [0 for _ in range(N)]

    for a in As:
        ans[a-1] += 1

    for a in ans:
        print(a)


if __name__ == "__main__":
    solve()
