# -*- coding:utf-8 -*-
import itertools

def solve():
    N, M = list(map(int, input().split()))
    Ks, Ss = [], []
    for i in range(M):
        _in = list(map(int, input().split()))
        Ks.append(_in[0])
        Ss.append(_in[1:])
    Ps = list(map(int, input().split()))

    # 全探索でいける
    switches = itertools.product([0,1], repeat=N)
    ans = 0
    for switch in switches:
        is_ok = True
        for i in range(M):
            on_num = 0
            for s in Ss[i]:
                if switch[s-1] == 1:
                    on_num += 1
            if on_num%2 != Ps[i]:
                is_ok = False
                break
        
        if is_ok:
            ans += 1

    print(ans)
    



if __name__ == "__main__":
    solve()
