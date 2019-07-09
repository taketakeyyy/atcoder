# -*- coding:utf-8 -*-

def solve():
    R, G, B, N = list(map(int, input().split()))

    ans = 0
    for r in range(N+1):
        if r*R > N: break
        
        for g in range(N+1):
            if r*R+g*G > N: break
            
            if (N - (r*R+g*G))%B == 0:
                ans += 1
    print(ans)

if __name__ == "__main__":
    solve()
