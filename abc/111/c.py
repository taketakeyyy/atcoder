# -*- coding: utf-8 -*-

def main():
    import collections

    n = int(input())
    vs = list(map(int, input().split()))

    vs_even = []
    vs_odd = []
    while True:
        if len(vs) == 0:
            break
        vs_odd.append(vs.pop(0))
        vs_even.append(vs.pop(0))

    if vs_even == vs_odd:
        # 1種類の数からなる数列のとき
        print(len(vs_even))
        exit()

    most_evens = collections.Counter(vs_even).most_common(2)
    most_odds = collections.Counter(vs_odd).most_common(2)

    len_vs_even = len(vs_even)
    if most_evens[0][0] == most_odds[0][0]:
        # 変換したら、1種類の数になってしまう
        # ex.) vs = [1 2 1 2 1 2 2 2 2 2 2 2 2 2]
        # ex.) vs = [1 1 1 1 1 1 3 2 3 2]
        # ので、2番目に大きい数字で変換する
        if most_evens[0][1] > most_odds[0][1]:
            ans = 0
            ans += len_vs_even - most_odds[1][1]
            ans += len_vs_even - most_evens[0][1]
            print(ans)
            exit()
        elif most_evens[0][1] == most_odds[0][1]:
            if most_evens[1][1] >= most_odds[1][1]:
                ans = 0
                ans += len_vs_even - most_evens[1][1]
                ans += len_vs_even - most_odds[0][1]
                print(ans)
                exit()
            else:
                ans = 0
                ans += len_vs_even - most_odds[1][1]
                ans += len_vs_even - most_evens[0][1]
                print(ans)
                exit()
        else:
            ans = 0
            ans += len_vs_even - most_evens[1][1]
            ans += len_vs_even - most_odds[0][1]
            print(ans)
            exit()
    # 変換しても、2種類の数になるならば
    ans = 0
    ans += len_vs_even - most_evens[0][1]
    ans += len_vs_even - most_odds[0][1]
    print(ans)



if __name__ == '__main__':
    main()
