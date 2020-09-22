# -*- coding:utf-8 -*-
"""考え方
・BBBBWWW
右にBを置けば良い

・WWBBWW
右にBを置く
右にWを置く

・WBWBWBWBBBBBBW
右にBWBWBWBWの順に置く
または、
左にBWBWBWBWの順に置く

どうやら、左と右でもかわらない様子
"""
def solve():
    S = input()

    ans = 0
    now = S[0]
    for i, moji in enumerate(list(S)):
        if now == moji:
            continue
        ans += 1
        now = moji
    print(ans)
    

if __name__ == "__main__":
    solve()
