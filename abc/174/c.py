# -*- coding:utf-8 -*-

def solve():
    K = int(input())
    a = 7%K
    i = 1
    Kset = set()
    Kset.add(a)
    while a!=0:
        a = (a*10+7)%K
        i += 1
        if a in Kset:
            print(-1)
            return
        Kset.add(a)
    print(i)


if __name__ == "__main__":
    solve()
