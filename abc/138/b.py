# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    total = 0
    for i in range(N):
        total += 1/As[i]
    
    print(1/total)

if __name__ == "__main__":
    solve()
