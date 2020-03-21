# -*- coding:utf-8 -*-

def is_prime(n):
    if n <= 1: return False

    i = 2
    while i*i <= n:
        if n%i == 0: return False
        i += 1
    return True


def solve():
    X = int(input())

    # Xから素数判定をすればよい
    x = X
    while not is_prime(x):
        x += 1
    print(x)


if __name__ == "__main__":
    solve()
