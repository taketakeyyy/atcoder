# -*- coding:utf-8 -*-

def solve():
    N = int(input())

    # 約数のペア(a,b)で、a+bが最小となるものが答え
    ans = float("inf")
    for i in range(1, N):
        if i > N**(1/2):
            break

        if N%i == 0:
            ans = min(ans, (i-1)+(N//i-1))
    print(ans)


if __name__ == "__main__":
    solve()
