# -*- coding:utf-8 -*-

def main():
    N = int(input())

    pre_t, pre_x, pre_y = 0, 0, 0
    for i in range(N):
        t, x, y = list(map(int, input().split()))
        diff = abs(x-pre_x) + abs(y-pre_y)
        amari = (t-pre_t) - diff
        if amari < 0:
            # 遠すぎて到達不可能
            print("No")
            exit()
        elif amari == 0:
            continue
        elif amari%2 == 0:
            # 余りが偶数なら目的地に戻れる
            continue
        else:
            print("No")
            exit()
    print("Yes")

if __name__ == "__main__":
    main()
