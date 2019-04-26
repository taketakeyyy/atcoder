# -*- coding:utf-8 -*-

def solve():
    N = int(input())
    S = input()

    kuro_num = 0
    siro_num = 0
    for moji in S:
        if moji == "#":
            kuro_num += 1
        else:
            siro_num += 1

    """
    ######################
    .#####################
    ..####################
    (略)
    ..........############
    (略)
    ....................##
    .....................#
    ......................
    の全パターンのうち、最も回数が少ないものが答え
    """
    right_kuro_num = kuro_num
    right_siro_num = siro_num
    ans = siro_num
    for moji in S:
        if moji == "#":
            right_kuro_num -= 1
        else:
            right_siro_num -= 1
        num = right_siro_num + (kuro_num - right_kuro_num)
        ans = min(ans, num)

    print(ans)

"""
26
...##..##...##.....#..#..#
"""
if __name__ == "__main__":
    solve()