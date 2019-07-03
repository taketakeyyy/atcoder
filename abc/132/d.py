# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(100000)  # RecursionError対策


def solve():
    N, K = list(map(int, input().split()))
    MOD = 10**9+7

    """
    青をi個のゾーンに区別可能か？
    """

    op_dict = {}
    for i in range(1, K+1):
        op_dict[i] = 0

    def dfs(depth, rest_r, rest_b, pre_ball, op_cnt):
        if depth == N or rest_b==0 or (rest_r==0 and pre_ball=="B"):
            op_dict[op_cnt] += 1
            op_dict[op_cnt] %= MOD
            return
        
        if rest_r != 0:
            dfs(depth+1, rest_r-1, rest_b, "R", op_cnt)
        
        if rest_b != 0:
            if pre_ball != "B":
                op_cnt += 1
            dfs(depth+1, rest_r, rest_b-1, "B", op_cnt)
        return
    
    dfs(0, N-K, K, "NULL", 0)

    for i in range(1, K+1):
        print(op_dict[i])
        




if __name__ == "__main__":
    solve()
