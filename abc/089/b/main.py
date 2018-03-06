#-*- coding:utf-8 -*-

if __name__ == "__main__":
    # Yが存在したらfour
    N = int(input())
    S = input().split()
    for c in S:
        if c == "Y":
            print("Four")
            exit()
    print("Three")
