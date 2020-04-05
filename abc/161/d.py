# -*- coding:utf-8 -*-
import copy

def solve():
    K = int(input())

    if K <= 9:
        print(K)
        return

    que = [i for i in range(1, 10)]
    cnt = 9

    while True:
        tmp_que = copy.deepcopy(que)
        que = []
        for i in tmp_que:
            a = i%10
            for j in range(a-1, a+2):
                if j < 0 or j > 9:
                    continue
                cnt += 1
                new = i*10+j
                if K == cnt:
                    print(new)
                    return
                que.append(new)


if __name__ == "__main__":
    solve()
