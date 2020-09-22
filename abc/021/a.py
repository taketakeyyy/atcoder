# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    ans = []
    while N != 0:
        N -= 1
        ans.append(1)

    print(len(ans))
    for i in range(len(ans)):
        print(ans[i])


if __name__ == "__main__":
    solve()
