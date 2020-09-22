# -*- coding: utf-8 -*-

def main():
    l = list(map(int, input().split()))
    l.sort()
    print(l[2]*10+l[1]+l[0])


if __name__ == '__main__':
    main()
