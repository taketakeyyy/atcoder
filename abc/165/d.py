# -*- coding:utf-8 -*-

def solve():
    A, B, N = list(map(int, input().split()))

    def f(x):
        return (A*x//B) - A*(x//B)

    # 分母のBに注目すると、1 <= x <= B　を調べれば良い
    if B > N:
        print(f(N))
    else:
        print(f(B-1))


if __name__ == "__main__":
    solve()
