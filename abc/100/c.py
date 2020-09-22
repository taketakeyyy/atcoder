# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    ans = 0
    #  素因数分解したときの2**x の xの総和が答え
    for a in A:
        while a%2 == 0:
            a = a / 2
            ans += 1
    
    print(ans)

if __name__ == "__main__":
    solve()