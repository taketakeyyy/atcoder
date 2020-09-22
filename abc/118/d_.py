from collections import defaultdict
from copy import copy

N,M = map(int,input().split())
A = list(map(int,input().split()))

ms = [2,5,5,4,5,6,3,7,6]
dic = defaultdict(lambda: 0)
for a in A:
    dic[ms[a-1]] = max(dic[ms[a-1]], a)

sd = sorted(dic.items())

dp = [None] * (N+1)
dp[0] = defaultdict(lambda: 0)

for i in range(sd[0][0], N+1):
    cands = []
    least_len = -1
    for l,a in sd:
        if i-l < 0: break
        if dp[i-l] is None: continue
        if cands and sum(dp[i-l].values())+1 < least_len:
            continue
        cands.append(copy(dp[i-l]))
        cands[-1][a] += 1
        least_len = sum(cands[-1].values())
    if not cands: continue
    max_v = 0
    max_j = -1
    for j,cand_dic in enumerate(cands):
        tmp_s = ''
        for a,n in sorted(cand_dic.items(), reverse=True):
            tmp_s += str(a) * n
        tmp_v = int(tmp_s)
        if tmp_v > max_v:
            max_v = tmp_v
            max_j = j
    dp[i] = cands[max_j]

ans = ''
for a,n in sorted(dp[-1].items(), reverse=True):
    ans += str(a) * n
print(ans)
