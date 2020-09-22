# -*- coding:utf-8 -*-

if __name__ == '__main__':
    S = input()
    T = input()
    S_ = S
    for i in range(len(S)):
        if S_ == T:
            print("Yes")
            exit()
        tmp = S_[0]
        S_ = S_[1:] + tmp
    print("No")
