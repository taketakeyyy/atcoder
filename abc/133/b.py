# -*- coding:utf-8 -*-
import math

def calc(x1, x2):
    ans = 0
    for i in range(len(x1)):
        ans += (x1[i]-x2[i])**2
    return float(math.sqrt(ans))

def solve():
    N, D = list(map(int, input().split()))
    X = []
    for i in range(N):
        X.append(list(map(int, input().split())))

    ans = 0
    for i in range(N):
        for j in range(i+1, N):
            ret = calc(X[i], X[j])
            if ret.is_integer():
                ans += 1

    print(ans)



if __name__ == "__main__":
    solve()
