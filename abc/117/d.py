# -*- coding:utf-8 -*-
"""
3 7
1 6 3

f(4) = (4^1)+(4^6)+(4^3)
     = 14

・(4^1)
100
001
---
101=5

・(4^6)
100
110
---
010=2

・(4^3)
100
011
---
111=7

・各bitが1か0どちらにしたらいいかを調べる

dp[i] := ibit目を1にするべきか（True/False）

・ibit目が0のときは、1+6+3=10なので、

・0bit目が1のときは、f(1) >= 10かどうかを調べる

・1bit目が1のときは、f(2) >= 10かどうかを調べる

Kの最大は K = 10**12 =< ((2**4)**12) = (2**48)
なので、最大50bitくらいを調べればよい
"""

"""解説

"""
def solve():
    N, K = list(map(int, input().split()))
    A = list(map(int, input().split()))

    dp = [False] * (51)
    sumA = sum(A)

    def f(i):
        """ ibit目を1にしたときのF(2**i)の値 """
        x = 2**i
        if x > sumA or x > K:
            return 0
        
        ans = 0
        for a in A:
            ans += x^a
        return ans

    for i in range(51):
        if f(i) > sumA:
            dp[i] = True

    x = 0
    for i in range(51):
        if dp[i]:
            x += 2**i

    ans = 0
    for a in A:
        ans += x^a
    print(ans)

if __name__ == "__main__":
    solve()