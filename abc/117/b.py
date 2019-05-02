# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    L = list(map(int, input().split()))
    L.sort()
    
    longest = L[-1]
    sum = 0
    for i in range(len(L)-1):
        sum += L[i]
    
    if longest < sum:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()