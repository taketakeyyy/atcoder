# -*- coding:utf-8 -*-

def solve():
    N, M = list(map(int, input().split()))

    """解放1
    (1) 2a+3b+4c = M
    (2)  a+ b+ c = N
    bを固定して（ループで回して）、2a+4c=M-3bで鶴亀算する
    """
    for b in range(0, 10**5+1):
        MM = M - 3*b
        # 2a + 4c = MM
        # を鶴亀算でO(1)で求める
        # aが鶴でcが亀。
        # a + c = N-bである。
        # 亀が0匹で全部が鶴だとすると、a = N-b
        diff = MM - 2*(N-b)
        # 鶴が一匹減り、亀が一匹増えると全体の足は2本増えるので、
        if diff%2 != 0 or diff < 0:
            continue
        c = diff//2
        a = N - b - c
        if a>=0 and c>=0:
            print(a,b,c)
            return
    print("-1 -1 -1")


if __name__ == "__main__":
    solve()
