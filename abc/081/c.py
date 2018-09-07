# -*- coding:utf-8 -*-

def zehnpaard():
    from collections import Counter

    n, k = map(int, input().split())
    c = Counter(int(x) for x in input().split())
    print(sum(val for key, val in c.most_common()[k:]))

def main():
    """WA"""
    N, K = list(map(int, input().split()))
    a_list = list(map(int, input().split()))

    import collections
    c_dict = collections.Counter(a_list)
    diff = len(c_dict) - K
    if diff <= 0:
        print(0)
        exit()

    # diff個消す。カウント数が少ないやつを。
    ans = 0
    c_list = sorted(c_dict.items(), key=lambda x: x[1])
    c_list[:diff]
    for i in range(diff):
        ans += c_list[i][1]
    print(ans)

def main2():
    N, K = list(map(int, input().split()))
    a_list = list(map(int, input().split()))

    import collections
    c_dict = collections.Counter(a_list)
    print(sum(value for key, value in c_dict.most_common()[K:]))

if __name__ == "__main__":
    main()
