# -*- coding:utf-8 -*-

def solve():
    K = int(input())
    S = input()

    if len(S) <= K:
        print(S)
    else:
        ans = S[0:K] + "..."
        print(ans)


if __name__ == "__main__":
    solve()
