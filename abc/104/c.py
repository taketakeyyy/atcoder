# -*- coding: utf-8 -*-
import math

def solve(D, G, Ps, Cs):
    """ 平均値が高いやつから解いていく戦略 """
    AvgRank = {}
    for i in range(1, D+1):
        avg = (Ps[i] * 100 * i + Cs[i]) / Ps[i]
        AvgRank[i] = [Ps[i], avg]
    AvgRanks = sorted(AvgRank.items(), key=lambda x: -x[1][1])

    rest_Is = []
    for i in range(1, D+1):
        rest_Is.append(i)

    solved = 0
    rest_G = G
    while True:
        """
        (1) 残っている問題の中から一番点数高い問題を全て解いてOKなら、そうする
        (2) それがだめなら、最も高い平均値のやつを解く
        (3) (2)の問題を除外し、(1)に戻る
        """
        i = rest_Is[-1]
        if rest_G <= (Ps[i] * 100*i):
            solved += math.ceil(G/(100*i))
        else:
            solved += AvgRanks[0][1][0]
            now_i   = AvgRanks[0][0]
            rest_Is.remove(now_i)
            AvgRanks.pop(0)
            rest_G -= (Ps[now_i] * 100*now_i)
            if rest_G <= 0:
                break
            else:
                continue
    print(solved)


if __name__ == "__main__":
    D, G = list(map(int, input().split()))
    Ps = [0]
    Cs = [0]
    for i in range(D):
        p, c = list(map(int, input().split()))
        Ps.append(p)
        Cs.append(c)

    solve(D, G, Ps, Cs)
