# -*- coding:utf-8 -*-
import sys


def solve():
    N, K = list(map(int, sys.stdin.readline().split()))
    Vs = list(map(int, sys.stdin.readline().split()))

    ans = 0
    for i in range(0, K+1):
        for j in range(0, K+1):
            if i+j > K: break
            if i+j > N: break

            _Vs = Vs[::-1]
            have = Vs[0:i]+_Vs[0:j]
            have.sort(reverse=True)

            M = i+j
            while M < K:
                if len(have) == 0: break
                if have[-1] < 0:
                    have.remove(have[-1])
                    M += 1
                    continue
                break

            ans = max(ans, sum(have))

    print(ans)



if __name__ == "__main__":
    solve()
