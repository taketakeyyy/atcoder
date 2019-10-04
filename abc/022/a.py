# -*- coding:utf-8 -*-

def solve():
    N, S, T = list(map(int, input().split()))
    W = int(input())
    As = []
    for i in range(N-1):
        As.append(int(input()))

    if S <= W <= T:
        ans = 1
    else:
        ans = 0
    X = W
    for i in range(N-1):
        X += As[i]
        if S <= X <= T:
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
