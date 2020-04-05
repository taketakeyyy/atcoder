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
            if 0 <= (a-1) <= 9:
                cnt += 1
                new = i*10 + (a-1)
                if K == cnt:
                    print(new)
                    return
                que.append(new)
            if 0 <= a <= 9:
                cnt += 1
                new = i*10 + a
                if K == cnt:
                    print(new)
                    return
                que.append(new)
            if 0 <= (a+1) <= 9:
                cnt += 1
                new = i*10 + (a+1)
                if K == cnt:
                    print(new)
                    return
                que.append(new)



if __name__ == "__main__":
    solve()
