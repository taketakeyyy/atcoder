# -*- coding:utf-8 -*-
"""
[入力例1]
 Rs\Cs  12002
 1      □■□□□
 2      ■□□□■
 2      □■□□■

"""

def solve():
    R, C, K = list(map(int, input().split()))
    N = int(input())

    Rs = [0]*R
    Cs = [0]*C
    candies = []
    for _ in range(N):
        r, c = list(map(int, input().split()))
        r, c = r-1, c-1
        candies.append((r,c))
        Rs[r] += 1
        Cs[c] += 1

    Rs_dict = {}  # R_dict[i] := Rsの要素がiの数
    Cs_dict = {}  # C_dict[i] := Csの要素がiの数
    for i in range(K+1):
        Rs_dict[i] = 0
    for i in range(K+1):
        Cs_dict[i] = 0

    for i in Rs:
        if i > K: continue
        Rs_dict[i] += 1
    for i in Cs:
        if i > K: continue
        Cs_dict[i] += 1

    # 答えを計算する
    ans = 0
    for i in range(K+1):
        ans += Rs_dict[i] * Cs_dict[K-i]

    # ただし、飴が置かれている箇所は例外パターンなので調整する
    for candy in candies:
        r, c = candy
        if Rs[r] + Cs[c] == K:
            ans -= 1
        elif Rs[r] + Cs[c] == K+1:
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
