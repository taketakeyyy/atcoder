# -*- coding:utf-8 -*-
import copy
from math import factorial

def solve2():
    N = int(input())
    cities = [[None, None]]
    for i in range(N):
        x, y = list(map(int, input().split()))
        cities.append([x,y])

    def calc_distance(a, b):
        return ((a[0]-b[0])**2+(a[1]-b[1])**2)**(1/2)

    memo = {}  # 距離の事前計算
    for i in range(1, N+1):
        for j in range(i+1, N+1):
            memo[(i,j)] = calc_distance(cities[i], cities[j])

    degree = N-1  # 頂点の次数
    coef = factorial(degree)

    ans = 0
    for key, value in memo.items():
        ans += value * coef * 2  # 経路(1,2)と経路(2,1)で倍にする必要がある
    ans = ans / factorial(N)
    print(ans)


def solve():
    N = int(input())
    cities = [[None, None]]
    for i in range(N):
        x, y = list(map(int, input().split()))
        cities.append([x,y])

    def calc_distance(a, b):
        return ((a[0]-b[0])**2+(a[1]-b[1])**2)**(1/2)

    memo = {}  # 距離の事前計算
    for i in range(1, N+1):
        for j in range(i+1, N+1):
            memo[(i,j)] = calc_distance(cities[i], cities[j])

    def dfs(will_visit, visited, now_i, total_d):
        if now_i is None:
            ans = 0
            for i in will_visit:
                new_will_visit = copy.deepcopy(will_visit)
                new_visited = copy.deepcopy(visited)
                new_will_visit.remove(i)
                new_visited.add(i)
                ans += dfs(new_will_visit, new_visited, i, 0)
            return ans

        if will_visit == []:
            return total_d

        ans = 0
        for i in will_visit:
            if i in visited: continue
            new_will_visit = copy.deepcopy(will_visit)
            new_visited = copy.deepcopy(visited)
            new_will_visit.remove(i)
            new_visited.add(i)
            ans += dfs(new_will_visit, new_visited, i, total_d+memo[min(now_i, i), max(now_i, i)])
        return ans

    will_visit = [i for i in range(1, N+1)]
    visited = set()
    ans = dfs(will_visit, visited, None, 0)
    print(ans/factorial(N))


if __name__ == "__main__":
    solve2()
