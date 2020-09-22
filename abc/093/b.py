#-*- coding:utf-8 -*-

if __name__ == "__main__":
    A, B, K = list(map(int, input().split()))
    end = A + K
    if end >= B+1:
        end = B + 1
    for i in range(A, end):
        print(i)
    if end == B + 1:
        exit()

    start = B - K + 1
    if start <= i:
        start = i + 1
    for j in range(start, B+1):
        print(j)
