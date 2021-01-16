# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))

    mxa = 0
    pre_ans = 0
    for i in range(N):
        mxa = max(mxa, As[i])
        ans = max(pre_ans, mxa*Bs[i])
        print(ans)
        pre_ans = ans

if __name__ == "__main__":
    solve()
