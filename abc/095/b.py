import math

if __name__ == "__main__":
    N, X = list(map(int, input().split()))
    sum_moto = 0

    moto = int(input())
    sum_moto += moto
    min_moto = moto
    for i in range(N-1):
        moto = int(input())
        sum_moto += moto
        if moto < min_moto:
            min_moto = moto
    amari = X - sum_moto
    n = math.floor(amari / min_moto)
    print(N + n)
