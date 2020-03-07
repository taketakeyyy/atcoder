# -*- coding:utf-8 -*-

def solve():
    N, A, B = list(map(int, input().split()))
    ans = (N//(A+B))*A
    N -= (N//(A+B))*(A+B)

    if A >= N:
        ans += N
    else:
        ans += A
    print(ans)



if __name__ == "__main__":
    solve()
