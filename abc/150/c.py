# -*- coding:utf-8 -*-
import copy

def solve():
    N = int(input())
    Ps = tuple(map(int, input().split()))
    Qs = tuple(map(int, input().split()))

    available_list = [i for i in range(1, N+1)]

    permutations = []  # 順列
    def _dfs(rest_list, p):
        if len(rest_list) == 0:
            permutations.append(tuple(p))
            return

        for i in range(1, N+1):
            if i in rest_list:
                tmp_rest_list = copy.deepcopy(rest_list)
                tmp_rest_list.remove(i)
                tmp_p = copy.deepcopy(p)
                tmp_p.append(i)
                _dfs(tmp_rest_list, tmp_p)


    _dfs(available_list, [])

    permutations.sort()

    for i, p in enumerate(permutations):
        if p == Ps:
            a = i+1
        if p == Qs:
            b = i+1

    print(abs(a-b))


if __name__ == "__main__":
    solve()
