# -*- coding:utf-8 -*-
class Person:
    def __init__(self, _id, mame):
        self.id = _id
        self.mame = mame
        self.juni = 0


def solve():
    A = int(input())
    B = int(input())
    C = int(input())
    ps = [Person(1, A), Person(2, B), Person(3, C)]
    ps.sort(key=lambda x: x.mame, reverse=True)

    # 順位の決定
    for i in range(len(ps)):
        ps[i].juni = i+1

    # 出力
    ps.sort(key=lambda x: x.id)
    for i in range(len(ps)):
        print(ps[i].juni)


if __name__ == "__main__":
    solve()
