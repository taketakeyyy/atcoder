#-*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    As = list(map(int, input().split()))
    As.sort(reverse=True)
    alice = 0
    bob   = 0
    for i in range(len(As)):
        if i%2 == 0:
            alice += As[i]
        else:
            bob   += As[i]
    print(alice - bob)
