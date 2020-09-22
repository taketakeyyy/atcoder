# prd_xxx氏の回答

N,M = map(int,input().split())
AB = [tuple(map(int,input().split())) for i in range(N)]

from collections import defaultdict
d = defaultdict(lambda: [])

for a,b in AB:
    d[a].append(b)

import heapq
class Heapq:
    def __init__(self, arr, desc=False):
        if desc:
            arr = [-a for a in arr]
        self.sign = -1 if desc else 1
        self.hq = arr
        heapq.heapify(self.hq)

    def pop(self):
        return heapq.heappop(self.hq) * self.sign

    def push(self, a):
        heapq.heappush(self.hq, a * self.sign)

    def top(self):
        return self.hq[0] * self.sign

    def size(self):
        return len(self.hq)

q = Heapq([], True)

ans = 0
for i in range(1,M+1):
    for b in d[i]:
        q.push(b)
    if q.size():
        ans += q.pop()
print(ans)
