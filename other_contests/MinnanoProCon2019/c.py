# -*- coding:utf-8 -*-

def solve():
    K, A, B = map(int, input().split())
    """
    (1) A < B ならば、ビスケットを円に交換して、円からビスケットにする意味はある
    そうでなければ、ひたすらビスケットを割ったほうがよい

    (2) ビスケットを円にして、円からビスケットにするまでに2操作がかかる
    この一連の操作で3ビスケット以上稼げないなら、やらずにビスケットを割り続けたほうが良い
    """
    if A >= B:
        print(K+1)
        return

    if (B-A) < 3:
        print(K+1)
        return

    # x回為替ができるとしたら、
    # 2x + Ax <= K+1 となる最大のxを探す。
    x = (K+1)//(2+A)
    biscuit = (K+1)%(2+A)
    biscuit += B * x
    print(biscuit)

if __name__ == "__main__":
    solve()
