# -*- coding:utf-8 -*-
import sys

def solve():
    S = input()
    for i in range(len(S)):
        if (i+1)%2 == 0:
            # 偶数
            if S[i] in ("L", "U", "D"):
                continue
            else:
                print("No")
                return
        else:
            # 奇数
            if S[i] in ("R", "U", "D"):
                continue
            else:
                print("No")
                return
    print("Yes")


if __name__ == "__main__":
    solve()
