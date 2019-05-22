# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    A = list(map(int, input().split()))
    A.sort()

    cost = A[N-1] - A[0]
    ans = cost
    for i in range(1, N):
        if i+N-1 >= N:
            break
        cost = A[i+N-1] - A[i]
        ans = min(ans, cost)
    
    print(ans)


if __name__ == "__main__":
    solve()
