# -*- coding:utf-8 -*-
import math

def solve():
    N, A = map(int, input().split())
    team_num = N//3

    if team_num <= A:
        max_ans = team_num
    else:
        max_ans = A

    min_ans = math.ceil(A/3)

    print(min_ans, max_ans)


if __name__ == "__main__":
    solve()
