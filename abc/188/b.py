# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))
    ans = 0
    for i in range(N):
        ans += As[i]*Bs[i]

    if ans == 0:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
