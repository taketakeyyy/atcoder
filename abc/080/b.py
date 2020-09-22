# -*- coding:utf-8 -*-

def solve():
    N = input()
    X = int(N)

    total = 0
    while True:
        if len(N) == 0:
            break

        total += int(N[-1])
        N = N[:-1]
    
    if X%total == 0:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    solve()
