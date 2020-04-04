# -*- coding:utf-8 -*-

def solve():
    N, M = map(int, input().split())
    As = list(map(int, input().split()))

    total = sum(As)

    cnt = 0
    for a in As:
        if a >= total/(4*M):
            cnt += 1

    if cnt >= M:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
