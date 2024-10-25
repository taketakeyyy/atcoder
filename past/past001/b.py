# -*- coding:utf-8 -*-

def solve():
    import sys
    N = int(sys.stdin.readline())
    pre_a = int(sys.stdin.readline())

    for i in range(N-1):
        a = int(sys.stdin.readline())
        if pre_a == a:
            print("stay")
        elif pre_a < a:
            print("up {}".format(abs(pre_a-a)))
        else:
            print("down {}".format(abs(pre_a-a)))
        pre_a = a


if __name__ == "__main__":
    solve()
