# -*- coding:utf-8 -*-

def solve():
    S = input()
    ans = ""
    for moji in S:
        if moji == "O":
            ans += "A"
        elif moji == "A":
            ans += "O"
        else:
            ans += moji
    print(ans)


if __name__ == "__main__":
    solve()
