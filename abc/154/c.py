# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    As = list(map(int, input().split()))
    dic = {}

    for a in As:
        if not a in dic:
            dic[a] = True
            continue
        print("NO")
        return
    print("YES")


if __name__ == "__main__":
    solve()
