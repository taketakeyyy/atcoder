# -*- coding:utf-8 -*-
"""解説
二分探索 O(log(N))

あるxの地点での寺と神社に行くパターン数は、
・西に行き、寺か神社に行く
・東に行き、寺か神社に行く

その後、
・西に行き、寺か神社に行く
・東に行き、寺か神社に行く

の8パターンしかない。

"""
import bisect

def solve():
    A, B, Q = list(map(int, input().split()))
    S, T, X = [], [], []
    for i in range(A):
        S.append(int(input()))
    for i in range(B):
        T.append(int(input()))
    for i in range(Q):
        X.append(int(input()))
    INF = 10**11+1
    S.append(INF)
    S.append(-INF)
    T.append(INF)
    T.append(-INF)
    S.sort()
    T.sort()
    
    """
    ・x -> 最寄りのS -> 最寄りのT
    ・x -> 最寄りのT -> 最寄りのS
    のどちらか最小値が答え？
    """
    for q in range(Q):
        x = X[q]

        # x -> 左の神社 -> 寺パターン
        index = bisect.bisect_left(S, x)
        l_s_index, r_s_index = index-1, index

        tmp_ans = abs(S[l_s_index]-x)
        index_t = bisect.bisect_left(T, S[l_s_index])
        l_t_index, r_t_index = index_t-1, index_t
        ans = tmp_ans + abs(T[l_t_index]-S[l_s_index])
        ans = min(ans, tmp_ans + abs(T[r_t_index]-S[l_s_index]))

        # x -> 右の神社 -> 寺パターン
        tmp_ans = abs(S[r_s_index]-x)
        index_t = bisect.bisect_left(T, S[r_s_index])
        l_t_index, r_t_index = index_t-1, index_t
        ans = min(ans, tmp_ans+abs(T[l_t_index]-S[r_s_index]))
        ans = min(ans, tmp_ans+abs(T[r_t_index]-S[r_s_index]))

        # x -> 左の寺 -> 神社パターン
        index_t = bisect.bisect_left(T, x)
        l_t_index, r_t_index = index_t-1, index_t

        tmp_ans = abs(T[l_t_index]-x)
        index_s = bisect.bisect_left(S, T[l_t_index])
        l_s_index, r_s_index = index_s-1, index_s
        ans = min(ans, tmp_ans+abs(S[l_s_index]-T[l_t_index]))
        ans = min(ans, tmp_ans+abs(S[r_s_index]-T[l_t_index]))

        # x -> 右の寺 -> 神社パターン
        tmp_ans = abs(T[r_t_index]-x)
        index_s = bisect.bisect_left(S, T[r_t_index])
        l_s_index, r_s_index = index_s-1, index_s
        ans = min(ans, tmp_ans+abs(S[l_s_index]-T[r_t_index]))
        ans = min(ans, tmp_ans+abs(S[r_s_index]-T[r_t_index]))

        print(ans)


if __name__ == "__main__":
    solve()
