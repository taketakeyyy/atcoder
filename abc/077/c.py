# -*- coding: utf-8 -*-
def main():
    """ AC """
    import bisect
    N = int(input())
    As = sorted(list(map(int, input().split())))
    Bs = sorted(list(map(int, input().split())))
    Cs = sorted(list(map(int, input().split())))

    c_under_b = [0]*N #b(i)の下に置けるcの数
    a_on_b = [0]*N #b(i)の上に置けるaの数

    for i in range(len(Bs)):
        c_under_b[i] = N - bisect.bisect_right(Cs, Bs[i])

    for i in range(len(Bs)):
        a_on_b[i] = bisect.bisect_left(As, Bs[i])

    count = 0
    for i in range(len(Bs)):
        count += c_under_b[i] * a_on_b[i]
    print(count)

def main5():
    """ AC """
    import bisect
    N = int(input())
    As = sorted(list(map(int, input().split())))
    Bs = sorted(list(map(int, input().split())))
    Cs = sorted(list(map(int, input().split())))

    c_under_b = [] #b(i)の下に置けるcの数
    a_on_b = [] #b(i)の上に置けるaの数

    for b in Bs:
        i = bisect.bisect_right(Cs, b)
        c_under_b.append(N - i)

    for b in Bs:
        i = bisect.bisect_left(As, b)
        a_on_b.append(i)

    count = 0
    for i in range(len(Bs)):
        count += c_under_b[i] * a_on_b[i]
    print(count)

def main4():
    """ TLE """
    import bisect
    N = int(input())
    As = sorted(list(map(int, input().split())))
    Bs = sorted(list(map(int, input().split())))
    Cs = sorted(list(map(int, input().split())))

    c_under_b = [] #b(i)の下に置けるcの数
    a_on_b = [] #b(i)の上に置けるaの数

    for b in Bs:
        i = bisect.bisect_right(Cs, b)
        c_under_b.append(len(Cs[i:]))

    for b in Bs:
        i = bisect.bisect_left(As, b)
        a_on_b.append(len(As[:i]))

    count = 0
    for i in range(len(Bs)):
        count += c_under_b[i] * a_on_b[i]
    print(count)

def main3():
    """ TLE """
    import itertools
    N = int(input())
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))
    Cs = list(map(int, input().split()))

    As.sort()
    Bs.sort()
    Cs.sort()
    count = 0
    for c in Cs:
        for b in Bs:
            if c <= b:
                break
            for a in As:
                if b <= a:
                    break
                if c > b > a:
                    count += 1
    print(count)

def main2():
    """ TLE """
    import itertools
    N = int(input())
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))
    Cs = list(map(int, input().split()))

    count = 0
    for c in Cs:
        for b in Bs:
            for a in As:
                if a < b < c:
                    count += 1
    print(count)


if __name__ == '__main__':
    main()
