# -*- coding:utf-8 -*-

def solve():
    S = input()
    ans = 0
    left = 0
    right = len(S)-1
    while left <= right:
        if S[left] != S[right]:
            ans += 1
        left += 1
        right -= 1
    print(ans)


if __name__ == "__main__":
    solve()
