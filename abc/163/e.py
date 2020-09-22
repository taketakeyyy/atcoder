# -*- coding:utf-8 -*-
from collections import deque

class MyNumber():
    def __init__(self, a, i, N):
        self.distance = (N-1)/2 - i

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    dic = {}
    for i, a in enumerate(As):
        if not a in dic:
            dic[a] = []
        dic[a].append(i)

    keys = list(dic.keys())
    keys.sort(reverse=True)

    que = deque([i for i in range(0, N)])
    ans = 0
    for key in keys:
        cands = deque(dic[key])
        while len(cands) != 0:
            mni, mxi = cands[0], cands[-1]
            ret1_r, ret1_l = abs(que[-1]-mni), abs(que[0]-mni)
            ret2_r, ret2_l = abs(que[-1]-mxi), abs(que[0]-mxi)

            mx = max(ret1_r, ret1_l, ret2_r, ret2_l)
            ans += mx*key
            if mx == ret1_r:
                que.pop(), cands.popleft()
            elif mx == ret1_l:
                que.popleft(), cands.popleft()
            elif mx == ret2_r:
                que.pop(), cands.pop()
            else:
                que.popleft(), cands.pop()

    print(ans)


if __name__ == "__main__":
    solve()
