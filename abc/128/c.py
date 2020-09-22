# -*- coding:utf-8 -*-
from itertools import combinations
import copy

def solve2():
    """
    itertools.productを使えばもっとすっきり？
    """
    import itertools as it
    N, M = list(map(int, input().split()))
    K = []
    S = []
    for i in range(M):
        _in = list(map(int, input().split()))
        K.append(_in[0])
        S.append(_in[1:])
    P = list(map(int, input().split()))

    switch_stats = it.product((0,1), repeat=N)

    ans = 0
    for stats in switch_stats:
        is_ok = True
        for i in range(M):  # すべての電球において
            on_num = 0
            for s_i in S[i]:
                on_num += 1 if stats[s_i-1]==1 else 0
            if on_num%2 == P[i]:
                continue
            else:
                is_ok = False
        
        if is_ok:
            ans += 1
    
    print(ans)


def solve():
    N, M = list(map(int, input().split()))
    K = []
    S = []
    for i in range(M):
        _in = list(map(int, input().split()))
        K.append(_in[0])
        S.append(_in[1:])
    P = list(map(int, input().split()))

    """
    全探索
    計算量 O(2^N * M * max(len(S)))
    N=10, M=10でも、1024 * 10 * 10 くらい？
    """
    def dfs(switch_stats):
        if len(switch_stats)==N:
            is_ok = True
            for i in range(M):
                on_num = 0
                for switch_i in S[i]:
                    on_num += 1 if switch_stats[switch_i-1] == 1 else 0
                if on_num%2 == P[i]:
                    continue
                else:
                    is_ok = False
                    break
            
            if is_ok:
                return 1
            else:
                return 0
        switch_stats1 = copy.deepcopy(switch_stats)
        switch_stats1.append(0)
        ret1 = dfs(switch_stats1)
        switch_stats2 = copy.deepcopy(switch_stats)
        switch_stats2.append(1)
        ret2 = dfs(switch_stats2)
        return ret1 + ret2

    ans = dfs([])
    print(ans)


if __name__ == "__main__":
    solve2()
