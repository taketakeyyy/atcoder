# -*- coding: utf-8 -*-

def main():
    N = input()
    Ns = []
    for n in N:
        Ns.append(int(n))
    Ns.sort()
    a = Ns[0]

    while True:
        num = a*100+a*10+a
        if num >= int(N):
            print(num)
            exit()
        a += 1


if __name__ == '__main__':
    main()
