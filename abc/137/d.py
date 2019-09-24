# -*- coding:utf-8 -*-
import sys
import heapq
from collections import defaultdict

"""解説PDF
(1) 0日目から考えると、最初に選べるアルバイトが多すぎて、どれを適切に選んでいけばよいかわからない

(2) M日後から考えると、M日後からi日前には、A_i<=iとなるアルバイトしか選べないので、これで考えると貪欲的に解ける

"""
def solve():
    N, M = list(map(int, sys.stdin.readline().split()))
    jobs = defaultdict(lambda: [])

    # jobs[a] := 報酬がa日後に貰えるアルバイトのリスト
    for i in range(N):
        a, b = list(map(int, sys.stdin.readline().split()))
        jobs[a].append(b)

    ans = 0
    heap = []  # アルバイト候補
    for i in range(1, M+1):
        # M-i日目に何のアルバイトをすればよいかを考える
        for b in jobs[i]:
            # 候補の追加
            heapq.heappush(heap, -b)  # 最大値を根にするために、マイナスをかける

        if len(heap) != 0:
            # 候補の中で報酬が最大値を取り出す
            ans += -heapq.heappop(heap)

    print(ans)


if __name__ == "__main__":
    solve()
