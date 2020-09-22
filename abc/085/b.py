# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    D = []
    for i in range(N):
        D.append(int(input()))
    D.sort()
    
    pre_d = D[0]
    ans = 1
    for i in range(1, N):
        if pre_d < D[i]:
            pre_d = D[i]
            ans += 1
    print(ans)
    

if __name__ == "__main__":
    solve()
