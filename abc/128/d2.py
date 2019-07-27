# -*- coding:utf-8 -*-
import copy

def solve():
    N, K = list(map(int, input().split()))
    V = list(map(int, input().split()))
    
    ans = 0
    M = min(N,K)
    for l in range(M+1):
        having = []
        for r in range(M+1):
            if l+r > M: break
            if l+r == 0: continue
            # 左からl, 右からr個の宝石を取り出す
            having = V[:l] + V[::-1][:r]
            having.sort(reverse=True)

            restK = K - (l+r)

            for _ in range(restK):
                if len(having)!=0 and having[-1] < 0:
                    having.pop()
                    continue
                break

            ans = max(ans, sum(having))
    
    print(ans)

if __name__ == "__main__":
    solve()
