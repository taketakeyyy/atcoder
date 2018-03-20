#-*- coding: utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    T = {}
    for i in range(N):
        t, x, y = list(map(int, input().split()))
        T[t] = (x,y)
    ts = sorted(T)
    # 回答する
    now_p = (0,0)
    now_t = 0
    for t in ts:
        path = abs(T[t][0] - now_p[0]) + abs(T[t][1] - now_p[1])
        time = t - now_t
        remain = time - path
        if remain < 0:
            print("No")
            exit()
        elif remain == 0:
            continue
        elif remain > 0:
            if remain%2 == 0:
                continue
            else:
                print("No")
                exit()
    print("Yes")
