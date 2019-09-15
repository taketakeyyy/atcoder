# -*- coding:utf-8 -*-
import sys

class Job():
    """アルバイト"""
    def __init__(self, a, b):
        self.after_days = a # a日後に報酬をもらえる
        self.rewards = b    # 報酬

def solve():
    N, M = list(map(int, sys.stdin.readline().split()))

    jobs = []
    for _ in range(N):
        a, b = list(map(int, sys.stdin.readline().split()))
        jobs.append(Job(a,b))

    # 優先度付きキューで解く。
    # 解説放送とかPDFとかみるべし
    dp = [[0]*(M+1) for _ in range(N)]
    dp[0][0] = 0
    for i in range(N):
        for j in range(M+1):
            dp[i][j] = dp[]




if __name__ == "__main__":
    solve()
