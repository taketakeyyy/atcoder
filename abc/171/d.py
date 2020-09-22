# -*- coding:utf-8 -*-

def solve():
    """しゃくとり法で解く"""
    N = int(input())
    As = list(map(int, input().split()))

    # 数列Aの要素aが何個あるかを保持する辞書dic
    dic = {}
    for a in As:
        if not a in dic:
            dic[a] = 0
        dic[a] += 1

    S = sum(As)  # 総和

    # 各クエリでしゃくとりする
    Q = int(input())
    for q in range(Q):
        b, c = list(map(int, input().split()))
        if b in dic:
            if not c in dic:
                dic[c] = 0
            S -= b*dic[b]
            S += c*dic[b]
            dic[c] += dic[b]
            dic[b] = 0
        print(S)


if __name__ == "__main__":
    solve()
