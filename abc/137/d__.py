# Shizuma氏の回答

import heapq
#標準入力受け取り
N, M = list(map(int, input().split()))
jobs = [[] for _ in range(M)]

for i in range(N):
    d, r = list(map(int, input().split()))
    if d-1 < M:
        jobs[d-1].append(-r) #マイナスにしている

rewards = 0
heap = []

#解法
for i in range(M):
    #要素を一つづつヒープに追加
    for reward in jobs[i]:
        heapq.heappush(heap, reward)
    if len(heap) > 0:
        #最大値(最小値)をヒープから取り出し
        reward = heapq.heappop(heap)
        rewards += -reward#マイナスにしている

print(rewards)
