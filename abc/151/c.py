# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))

    ac_dic = {}
    wa_lst = [0 for _ in range(N+1)]
    ac_score, wa_score = 0, 0
    for i in range(M):
        p, s = input().split()
        p = int(p)

        if not p in ac_dic:
            if s == "WA":
                wa_lst[p] += 1
                ac_dic[p] = False
            else:
                ac_score += 1
                ac_dic[p] = True
        else:
            if s=="WA" and not ac_dic[p]:
                wa_lst[p] += 1
            elif s=="AC" and not ac_dic[p]:
                ac_score += 1
                ac_dic[p] = True

    # waスコアを数える
    for i, score in enumerate(wa_lst):
        if i in ac_dic and ac_dic[i]:
            wa_score += wa_lst[i]

    print(ac_score, wa_score)


if __name__ == "__main__":
    solve()
