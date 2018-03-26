#-*- coding:utf-8 -*-
import math

if __name__ == "__main__":
    N, K = list(map(int, input().split()))
    # (1)aがK以上のとき、 a<b を満たすものはありうる組となる
    # (2)ソレ以外のとき、愚直に計算する
    ans = 0
    #(1)
    n = (N-K)
    ans += int(n*(n+1)/2)
    #(2)
    for a in range(K, N+1):
        for b in range(1, a+1):
            if a%b >= K:
                ans += 1
    print(ans)
