# -*- coding: utf-8 -*-

def main():
    n, m, x, y = list(map(int, input().split()))
    Xs = list(map(int, input().split()))
    Ys = list(map(int, input().split()))
    Xs.append(x)
    Ys.append(y)
    Xs.sort()
    Ys.sort()

    if Xs[-1]+1 <= Ys[0]:
        print("No War")
        exit()
    print("War")


if __name__ == '__main__':
    main()
