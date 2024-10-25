# -*- coding:utf-8 -*-

def solve():
    S = input()

    strs = []
    start = False
    moji = ""
    for s in S:
        if s.isupper():
            moji += s
            if start:
                strs.append(moji.lower())
                moji = ""
            start = not start

        else:
            moji += s

    strs.sort()

    ans = ""
    for s in strs:
        ans += s[0].upper() + s[1:-1] + s[-1].upper()

    print(ans)


if __name__ == "__main__":
    solve()
