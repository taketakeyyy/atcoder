# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    ans = 0
    for i in range(N):
        X = S[:i+1]
        Y = S[i+1:]
        syurui = 0
        onaji = {}
        for x in X:
            if (x in Y) and (not x in onaji):
                onaji[x] = True
                syurui += 1
        ans = max(ans, syurui)
    print(ans)


if __name__ == "__main__":
    solve()
