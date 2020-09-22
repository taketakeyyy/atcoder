# -*- coding:utf-8 -*-
import sys
sys.setrecursionlimit(1000000)

def solve():
    N = int(input())
    persons = {}
    persons[1] = []
    for i in range(N-1):
        b = int(input())
        if not b in persons:
            persons[b] = []
        persons[b].append(i+2)
        if not (i+2) in persons:
            persons[i+2] = []


    def f(now):
        if len(persons[now]) == 0:
            return 1

        buka_salary = []
        bukas = persons[now]
        while len(bukas) != 0:
            buka = bukas.pop(-1)

            buka_salary.append(f(buka))

        buka_salary.sort()

        return buka_salary[0] + buka_salary[-1] + 1

    ans = f(1)
    print(ans)


if __name__ == "__main__":
    solve()
