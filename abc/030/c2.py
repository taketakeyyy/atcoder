# -*- coding:utf-8 -*-
import sys
import bisect


def solve():
    N, M = list(map(int, sys.stdin.readline().split()))
    X, Y = list(map(int, sys.stdin.readline().split()))
    As = list(map(int, sys.stdin.readline().split()))
    Bs = list(map(int, sys.stdin.readline().split()))
    As.sort()
    Bs.sort()

    ans = 0
    now_pos = "A"
    now_time = 0
    while True:
        if now_pos == "A":
            i = bisect.bisect_left(As, now_time)
            if i >= N: break
            now_time = As[i] + X
            now_pos = "B"
        else:
            i = bisect.bisect_left(Bs, now_time)
            if i >= M: break
            now_time = Bs[i] + Y
            now_pos = "A"
            ans += 1

    print(ans)



if __name__ == "__main__":
    solve()
