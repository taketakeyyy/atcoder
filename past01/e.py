# -*- coding:utf-8 -*-

def solve():
    import sys
    import numpy as np
    N, Q = list(map(int, sys.stdin.readline().split()))

    follow_states = [[0 for _ in range(N)] for _ in range(N)]  # follow_state[a][b] := aはbをフォローしている
    follow_states = np.array(follow_states)

    for _ in range(Q):
        S = list(map(int, sys.stdin.readline().split()))

        if S[0] == 1:
            # フォロー
            a, b = S[1]-1, S[2]-1
            follow_states[a][b] = 1

        elif S[0] == 2:
            a = S[1]-1

            for n in range(N):
                follow_states[a][n] |= follow_states[n][a]

        elif S[0] == 3:
            a = S[1]-1
            ns = []
            for n in range(N):
                if follow_states[a][n] == 1:
                    ns.append(n)
            for n in ns:
                follow_states[a] |= follow_states[n]
                follow_states[a][a] = 0


    for i in range(N):
        for j in range(N):
            if follow_states[i][j] == 1:
                print("Y", end="")
            else:
                print("N", end="")
        print()




if __name__ == "__main__":
    solve()
