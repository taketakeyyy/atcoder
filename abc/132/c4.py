# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    D = list(map(int, input().split()))
    D.sort()

    i = N//2

    if D[i] == D[i-1]:
        print(0)
        return
    
    print(D[i]-D[i-1])

if __name__ == "__main__":
    solve()
