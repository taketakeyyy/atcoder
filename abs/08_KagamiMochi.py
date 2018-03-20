#-*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    D = []
    for i in range(N):
        D.append(int(input()))
    D.sort(reverse=True)
    # 直径が大きいものから順に、重ねていく数を数える
    now_d = D[0]
    ans = 1
    for i in range(1, len(D)):
        if D[i] < now_d:
            ans += 1
            now_d = D[i]
    print(ans)
