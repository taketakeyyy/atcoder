# -*- coding:utf-8 -*-

def main():
    # TLE
    N = int(input())
    a_list = list(map(int, input().split()))

    # 初期設定
    ans = 0
    a_set = set(a_list)

    for a in a_set:
        c = a_list.count(a) # 要素の出現回数をカウントする
        if c < a:
            ans += c
        elif c > a:
            ans += c-a
    print(ans)

def main2():
    N = int(input())
    a_list = list(map(int, input().split()))
    ans = 0

    import collections
    count_dict = collections.Counter(a_list) # キーに要素、値に出現回数の辞書

    for key in count_dict:
        diff = key - count_dict[key]
        if diff == 0:
            continue
        elif diff > 0:
            ans += count_dict[key]
        elif diff < 0:
            ans += abs(diff)
    print(ans)



if __name__ == "__main__":
    main2()
