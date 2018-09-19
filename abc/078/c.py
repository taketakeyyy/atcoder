# -*- coding: utf-8 -*-

def main():
    N, M = list(map(int, input().split()))

    expected = 2**M * (1900*M + 100*(N-M))
    print(expected)

def main2():
    N, M = list(map(int, input().split()))

    inf_geo_series_k = lambda r: r/(1-r)**2
    a = inf_geo_series_k((2**M-1)/2**M)
    b = (1800*M + 100*(N-M)) / (2**M - 1)
    expected = a * b
    print(expected)


if __name__ == '__main__':
    main2()
