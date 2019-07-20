# -*- coding:utf-8 -*-

def solve():
    N = input()

    is_same = True
    num = N[0]
    for i in range(1, len(N)):
        if num == N[i]:
            continue
        is_same = False
        break

    if is_same:
        print("SAME")
    else:
        print("DIFFERENT")

if __name__ == "__main__":
    solve()
