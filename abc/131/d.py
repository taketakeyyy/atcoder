# -*- coding:utf-8 -*-
import sys

class Work():

    def __init__(self, a, b):
        self.need_time = a  # 仕事を終わらせるのに必要な時間
        self.deadline = b   # 締め切り時刻


def solve():
    N = int(input())

    works = []
    for _ in range(N):
        a, b = list(map(int, sys.stdin.readline().split()))
        works.append(Work(a, b))
    works.sort(key=lambda x: x.deadline)  # 締め切りが早い順にソート

    # 締切が早いやつから先に仕事を終らせる貪欲法
    now_time = 0  # 現在時刻
    for i in range(N):
        now_time += works[i].need_time
        if now_time > works[i].deadline:
            print("No")
            return
    print("Yes")



if __name__ == "__main__":
    solve()
