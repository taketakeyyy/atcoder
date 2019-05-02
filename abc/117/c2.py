# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))
    X = list(map(int, input().split()))

    X.sort()
    diffs = []
    for i in range(len(X)-1):
        diffs.append(abs(X[i]-X[i+1]))
    
    diffs.sort()

    ans = 0
    for i in range(len(diffs) - (N-1)):
        ans += diffs[i]
    
    print(ans)

if __name__ == "__main__":
    solve()