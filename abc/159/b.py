# -*- coding:utf-8 -*-

def is_kaibun(s):
    left = 0
    right = len(s)-1
    while left <= right:
        if s[left] != s[right]:
            return False
        left += 1
        right -= 1
    return True

def solve():
    S = input()
    N = len(S)

    if is_kaibun(S) and is_kaibun(S[0:(N-1)//2]) and is_kaibun(S[(N+3)//2-1:]):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
