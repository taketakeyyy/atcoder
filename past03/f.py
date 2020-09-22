# -*- coding:utf-8 -*-

def solve():
    import sys

    class Moji():
        def __init__(self, moji, num):
            self.moji = moji
            self.num = num



    N = int(sys.stdin.readline())
    As = []
    dic = {}
    for _ in range(N):
        A = sys.stdin.readline().rstrip()
        As.append(A)
        for a in A:
            if not a in dic:
                dic[a] = 0
            dic[a] += 1

    mojis = []
    for key, value in dic.items():
        m = Moji(key, value)
        mojis.append(m)

    mojis.sort(key=lambda m: m.num, reverse=True)

    only_amari = False  # あとはあまりをセットしたら終わりかどうか
    amari_moji = ""
    left_str, right_str = "", ""
    for moji in mojis:
        if only_amari and amari_moji != "":
            ans = left_str + amari_moji + right_str
            print(ans)
            return

        if N == 0:
            ans = left_str + right_str
            print(ans)
            return

        n = moji.num//2
        amari = moji.num%2
        if amari == 1 and amari_moji == "":
            amari_moji = moji.moji

        if n*2 >= N:
            n = N//2
            left_str = left_str + moji.moji*n
            right_str = moji.moji*n + right_str
            N -= n*2

            if N == 1:
                only_amari = True
                continue

            ans = left_str + right_str
            print(ans)
            return
        else:
            left_str = left_str + moji.moji*n
            right_str = moji.moji*n + right_str
            N -= n*2

        if N == 1:
            only_amari = True
            continue

    print(-1)




if __name__ == "__main__":
    solve()
