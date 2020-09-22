# -*- coding:utf-8 -*-
import copy

def solve():
    N, M = list(map(int, input().split()))
    paths = [[] for _ in range(N+1)]
    for i in range(M):
        u, v, l = list(map(int, input().split()))
        paths[u].append((v, l))
        paths[v].append((u, l))

    def dfs(house, will_visit, used_paths, cost, ans):
        if cost >= ans:
            return ans

        new_will_visit = copy.deepcopy(will_visit)

        while len(new_will_visit) != 0:
            h, l = new_will_visit.pop()
            path_ = (min(house, h), max(house, h))

            if path_ in used_paths:
                continue

            if h == 1:
                ans = min(ans, cost+l)
                continue

            new_used_paths = copy.deepcopy(used_paths)
            new_used_paths.add(path_)

            ans = min(ans, dfs(h, paths[h], new_used_paths, cost+l, ans))

        return ans


    # 答えを出力する
    ans = dfs(1, paths[1], set(), 0, float("inf"))
    if ans == float("inf"):
        print(-1)
    else:
        print(ans)


if __name__ == "__main__":
    solve()
