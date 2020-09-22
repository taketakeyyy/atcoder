# -*- coding:utf-8 -*-

def solve():
    N, M, K = list(map(int, input().split()))
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))

    sumAs = [0]*(N+1)
    for i in range(1, N+1):
        sumAs[i] = sumAs[i-1] + As[i-1]

    sumBs = [0]*(M+1)
    for i in range(1, M+1):
        sumBs[i] = sumBs[i-1] + Bs[i-1]

    i = 0
    while True:
        if i==(N+1) or sumAs[i] > K:
            break
        i += 1
    i = max(0, i-1)

    j = 0
    while True:
        if j==(M+1) or sumBs[j] + sumAs[i] > K:
            break
        j += 1
    j = max(0, j-1)

    ans = i+j

    # iを少しずつ減らし、jをその分増やし、最適解を見つける
    for n in range(i, -1, -1):
        while True:
            if j==(M+1) or sumBs[j] + sumAs[n] > K:
                break
            j += 1
        j = max(0, j-1)
        ans = max(ans, n+j)

    print(ans)


if __name__ == "__main__":
    solve()
