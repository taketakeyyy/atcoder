# -*- coding:utf-8 -*-

def solver():
    # mr.zehnpaard
    n, y = map(int, input().split())

    all1000s = y // 1000
    x = all1000s - n

    for a in range(0, x+1, 4):
        nines = (x - a) // 9
        fours = a // 4
        ones = n - nines - fours
        if (x - a) % 9 == 0 and all(x >= 0 for x in (nines, fours, ones)):
            print("{} {} {}".format(nines, fours, ones))
            break
    else:
        print("-1 -1 -1")


def main():
    # 9 45000
    N, Y = list(map(int, input().split()))

    # implements
    for x in range(N+1):
        for y in range(N+1):
            z = N - (x + y)
            if z < 0:
                break
            if (10000*x + 5000*y + 1000*z) == Y:
                print("{} {} {}".format(x, y, z))
                exit()
    print("-1 -1 -1")


if __name__ == "__main__":
    main()
