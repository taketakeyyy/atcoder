# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    Ls = list(map(int, input().split()))

    ans = 0
    for i in range(N):
        for j in range(i+1, N):
            for k in range(j+1, N):
                if Ls[i] < Ls[j]+Ls[k] and Ls[j] < Ls[k]+Ls[i] and Ls[k] < Ls[j]+Ls[i]:
                    if Ls[i] != Ls[j] and Ls[j] != Ls[k] and Ls[k] != Ls[i]:
                        ans += 1
    print(ans)

if __name__ == "__main__":
    solve()
