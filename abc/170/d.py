# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))

    As.sort()

    setA = set(As)
    setDel = set()

    cands = []

    for a in As:
        if a in setDel:
            continue

        i = 1
        while a*i <= As[-1]:
            if a*i in setA:
                setDel.add(a*i)
            i += 1

        cands.append(a)

    # 重複する数字を調べる
    dic = {}
    for a in As:
        if not a in dic:
            dic[a] = 0
        dic[a] += 1

    ans = 0
    for x in cands:
        if dic[x] > 1:
            continue
        ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
