# -*- coding:utf-8 -*-
"""貪欲法
"""
def solve():
    N, x = list(map(int, input().split()))
    A = list(map(int, input().split()))

    ans = 0

    total = A[1] + A[0]
    if total > x:
        diff = min(total-x, A[1])
        A[1] -= diff
        ans += diff

    total = A[1] + A[0]
    if total > x:
        diff = total - x
        A[0] -= diff
        ans += diff

    for i in range(2, N):
        total = A[i] + A[i-1]

        if total > x:
            diff = total - x
            A[i] -= diff
            ans += diff
    
    print(ans)


if __name__ == "__main__":
    solve()
