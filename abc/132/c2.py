# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    D = list(map(int, input().split()))

    D.sort()
    i = N//2

    if D[i] != D[i-1]:
        # 同じ数になるように分けることが可能
        print(D[i]-D[i-1])
        return
    print(0)
    

if __name__ == "__main__":
    solve()
