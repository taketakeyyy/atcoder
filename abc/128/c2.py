# -*- coding:utf-8 -*-
from itertools import product

def solve():
    N, M = list(map(int, input().split()))
    K, S = [], []
    for _ in range(M):
        _in = list(map(int, input().split()))
        K.append(_in[0])
        S.append(_in[1:])
    P = list(map(int, input().split()))

    all_stats = product((0,1), repeat=N)
    ans = 0
    for stat in all_stats:
        is_ok = True
        for switch_i, switch in enumerate(S):
            on_num = 0
            for i in range(len(switch)):
                if stat[switch[i]-1] == 1:
                    on_num += 1
            if on_num%2 != P[switch_i]:
                is_ok = False
                break
        if is_ok:
            ans += 1
    print(ans)

if __name__ == "__main__":
    solve()
