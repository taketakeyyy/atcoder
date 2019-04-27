# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    if N == 2:
        ans = max(A[0]+A[1], -A[0]+(-A[1]))
        print(ans)
        return

    # マイナスが奇数の時、好きな数字をマイナスにできる
    # マイナスが偶数の時、全てプラスにできる
    minus_num = 0
    for a in A:
        if a < 0:
            minus_num += 1
    
    ans = 0
    lowest = 10**9+1
    for a in A:
        ans += abs(a)
        if lowest >= abs(a):
            lowest = abs(a)
    
    if minus_num%2 == 0:
        print(ans)
    else:
        ans -= lowest*2
        print(ans)


if __name__ == "__main__":
    solve()
