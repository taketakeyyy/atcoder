# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    S = input()
    
    ans = ""
    for i in range(N):
        if i == K-1:
            ans += S[i].lower()
            continue
        ans += S[i]
    print(ans)

if __name__ == "__main__":
    solve()
