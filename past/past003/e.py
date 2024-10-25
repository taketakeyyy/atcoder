# -*- coding:utf-8 -*-

def solve():
    import sys

    N, M, Q = list(map(int, sys.stdin.readline().split()))
    Vs = [[] for _ in range(N)]

    for m in range(M):
        u, v = list(map(int, sys.stdin.readline().split()))
        u, v = u-1, v-1
        Vs[u].append(v)
        Vs[v].append(u)

    Cs = list(map(int, sys.stdin.readline().split()))

    for _ in range(Q):
        S = list(map(int, sys.stdin.readline().split()))

        if S[0] == 1:
            x = S[1]-1
            print(Cs[x])

            for v in Vs[x]:
                Cs[v] = Cs[x]

        elif S[0] == 2:
            x, y = S[1]-1, S[2]
            print(Cs[x])
            Cs[x] = y


if __name__ == "__main__":
    solve()
