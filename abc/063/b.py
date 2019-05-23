# -*- coding:utf-8 -*-

def solve():
    S = input()

    for i in range(len(S)):
        target = S[i]
        for j in range(i+1, len(S)):
            if target != S[j]:
                continue
            print("no")
            return
    print("yes")


if __name__ == "__main__":
    solve()
