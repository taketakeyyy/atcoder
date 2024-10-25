# -*- coding:utf-8 -*-

def solve():
    N, M, Q = list(map(int, input().split()))

    solved = [[] for _ in range(N)]  # といた問題の番号
    problems = [N for _ in range(M)]

    def calc_score(n):
        total = 0
        for m in solved[n]:
            total += problems[m]
        return total

    for _ in range(Q):
        S = list(map(int, input().split()))

        if S[0] == 1:
            print(calc_score(S[1]-1))

        else:
            solved[S[1]-1].append(S[2]-1)
            problems[S[2]-1] -= 1


if __name__ == "__main__":
    solve()
