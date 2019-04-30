# -*- coding:utf-8 -*-

def solve():
    S = input()
    y, m, d = list(map(int, S.split("/")))

    if y < 2019:
        print("Heisei")
    elif y==2019 and m <= 4:
        print("Heisei")
    else:
        print("TBD")

if __name__ == "__main__":
    solve()
