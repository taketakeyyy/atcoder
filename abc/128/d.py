# -*- coding:utf-8 -*-
from collections import deque

def solve():
    N, K = list(map(int, input().split()))
    V = list(map(int, input().split()))
    V = deque(V)

    """考え方
    DFS
    """

    import copy
    i_have1 = []
    i_have2 = []
    i_have3 = []
    i_have4 = []

    V1 = copy.deepcopy(V)
    V2 = copy.deepcopy(V)
    V3 = copy.deepcopy(V)
    V4 = copy.deepcopy(V)

    def dfs(depth):
        if depth == K:
            return
        
        if len(V1) >= 1:
            # 操作A
            a = V1.popleft()
            i_have1.append(a)
            dfs(depth+1)

        if len(V2) >= 1:
            # 操作B
            a = V2.pop()
            i_have2.append(a)
            dfs(depth+1)
        
        if len(i_have3) >= 1:
            min_v = min(i_have3)
            # 操作C
            V3.appendleft(min_v)
            dfs(depth+1)

        if len(i_have4) >= 1:
            # 操作D
            min_v = min(i_have4)
            V4.append(min_v)
            dfs(depth+1)
        
        return
    
    ans = dfs(0, [], V)

    print(ans)


if __name__ == "__main__":
    solve()
