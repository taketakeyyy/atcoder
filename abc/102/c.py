# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))

    for i in range(0, N):
        A[i] = A[i] - (i+1)
    
    sorted_A = sorted(A)
    b = sorted_A[N//2]

    ans = 0
    for i in range(0, N):
        ans += abs(A[i] - b)

    print(ans)

if __name__ == "__main__":
    solve()