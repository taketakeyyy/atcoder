# -*- coding:utf-8 -*-
"""
・pattern1が存在する場合
|<WBWBWWBWBWBW>WBWBWWBW|
|WWBWBWBW<WBWBWWBWBWBW>|
・pattern1が存在しない場合、pattern2で探す
|<BWWBWBWBWWBW>BWWBWBWB|
|WBWBWWBW<BWWBWBWBWWBW>|

"""

def solve():
    S = input()
    pattern1 = "WBWBWWBWBWBW"  # ド ド# レ レ# ミ ファ ファ# ソ ソ# ラ ラ# シ
    pattern2 = "BWWBWBWBWWBW"  # レ# ミ ファ ファ# ソ ソ# ラ ラ# シ ド ド# レ

    doremi1 = ["Do", "Do#", "Re", "Re#", "Mi", "Fa", "Fa#", "So", "So#", "La", "La#", "Si"]
    doremi2 = ["Re#", "Mi", "Fa", "Fa#", "So", "So#", "La", "La#", "Si", "Do", "Do#", "Re"]
    
    i = S.find(pattern1)
    if i >= 0:
        # pattern1が存在する
        ans = doremi1[-i]
    else:
        # pattern2が存在する
        i = S.find(pattern2)
        ans = doremi2[-i]

    print(ans)


if __name__ == "__main__":
    solve()
