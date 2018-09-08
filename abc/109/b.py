# -*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    pre_w = input()
    words = [pre_w]
    for i in range(N-1):
        w = input()
        if w in words:
            print("No")
            exit()
        words.append(w)

        if pre_w[-1] == w[0]:
            pre_w = w
            continue
        else:
            print("No")
            exit()
    print("Yes")
