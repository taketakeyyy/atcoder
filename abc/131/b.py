# -*- coding:utf-8 -*-

def solve():
    N, L = list(map(int, input().split()))
    all_taste = 0
    eat_taste = float("inf")
    for i in range(1, N+1):
        all_taste += L+i-1
        eat_taste = min(eat_taste, abs(L+i-1))
    
    ans = all_taste - eat_taste
    print(ans)



if __name__ == "__main__":
    solve()
