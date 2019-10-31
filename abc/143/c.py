# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    pre_color = S[0]
    ans = 1
    for i in range(1, N):
        color = S[i]

        if pre_color == color:
            continue
        else:
            ans += 1
            pre_color = color

    print(ans)

if __name__ == "__main__":
    solve()
