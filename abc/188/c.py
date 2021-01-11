# -*- coding:utf-8 -*-

def solve():
    import copy

    N = int(input())
    As = list(map(int, input().split()))
    sensyu = []
    for i, v in enumerate(As):
        sensyu.append((i+1, v))

    while 1:
        if len(sensyu) == 2:
            break

        next_sensyu = []
        cnt = 0
        for iv in sensyu:
            cnt += 1
            if cnt == 1:
                sensyu1 = iv
            else:
                sensyu2 = iv
                if sensyu1[1] > sensyu2[1]:
                    next_sensyu.append(sensyu1)
                else:
                    next_sensyu.append(sensyu2)
                cnt = 0
                continue
        sensyu = next_sensyu

    if sensyu[0][1] > sensyu[1][1]:
        print(sensyu[1][0])
    else:
        print(sensyu[0][0])


if __name__ == "__main__":
    solve()
