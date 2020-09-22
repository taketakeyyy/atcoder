# -*- coding:utf-8 -*-
from collections import deque

def solve():
    d = deque(input())
    Q = int(input())

    is_reverse = False # 反転中か？

    for _ in range(Q):
        query = input()
        if query == "1":
            is_reverse = not is_reverse
        else:
            _, f, c = query.split()

            if f == "1":
                if is_reverse:
                    # 末尾にcを追加
                    d.append(c)
                else:
                    # 先頭にcを追加
                    d.appendleft(c)
            else:
                if is_reverse:
                    # 先頭に追加
                    d.appendleft(c)
                else:
                    # 末尾に追加
                    d.append(c)

    if is_reverse:
        print("".join(reversed(list(d))))
    else:
        print("".join(d))


def solve2():
    S = list(input())
    Q = int(input())
    M = 2*10**5+10
    data = [None]*M
    data.extend(S)
    data.extend([None]*M)
    left, right = M-1, M+len(S)

    is_reverse = False

    for _ in range(Q):
        query = input()
        if query == "1":
            is_reverse = not is_reverse
        else:
            t, f, c = query.split()
            if f == "1":
                if is_reverse:
                    # 末尾にcを追加
                    data[right] = c
                    right += 1
                else:
                    # 先頭にcを追加
                    data[left] = c
                    left -= 1
            else:
                if is_reverse:
                    # 先頭に追加
                    data[left] = c
                    left -= 1
                else:
                    # 末尾に追加
                    data[right] = c
                    right += 1

    # 出力
    if is_reverse:
        print("".join(data[right-1:left:-1]))
        # for i in range(right-1, left, -1):
        #     print(data[i], end="")
    else:
        # for i in range(left+1, right):
        #     print(data[i], end="")
        print("".join(data[left+1:right]))
    # print()


if __name__ == "__main__":
    solve2()
