# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Xs = list(map(int, input().split()))

    avg1 = sum(Xs)//N
    avg2 = avg1+1

    ans1 = 0
    ans2 = 0
    for x in Xs:
        ans1 += (x-avg1)**2
        ans2 += (x-avg2)**2
    print(min(ans1, ans2))


if __name__ == "__main__":
    solve()
