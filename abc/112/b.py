# -*- coding: utf-8 -*-

def main():
    N, T = list(map(int, input().split()))
    paths = []
    for i in range(N):
        c, t = list(map(int, input().split()))
        paths.append((c, t))
    paths = sorted(paths, key=lambda x: x[0])

    for p in paths:
        if p[1] <= T:
            print(p[0])
            exit()
    print("TLE")


if __name__ == '__main__':
    main()
