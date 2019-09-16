# -*- coding:utf-8 -*-
import sys
import heapq

# http://prd-xxx.hateblo.jp/entry/2019/06/24/235844
# 丸パクリです
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


def solve():
    N, M = list(map(int, sys.stdin.readline().split()))
    As = list(map(int, sys.stdin.readline().split()))
    h = Heapq([], True)
    for i, a in enumerate(As):
        h.push(a)

    for i in range(M):
        a = h.pop()//2
        h.push(a)

    ans = 0
    for i in range(N):
        ans += h.pop()

    print(ans)



if __name__ == "__main__":
    solve()
