# -*- coding:utf-8 -*-

def solve():
    S = input()

    num0 = 0
    num1 = 0
    for moji in S:
        if moji == "0":
            num0 += 1
        else:
            num1 += 1
    erase_num = min(num0, num1)
    print(erase_num*2)


if __name__ == "__main__":
    solve()
