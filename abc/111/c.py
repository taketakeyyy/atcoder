# -*- coding:utf-8 -*-

def solve():
    n = int(input())
    V = [None]
    V.extend(list(map(int, input().split(" "))))
    
    # 1種類の数字で構成されているか？
    tmp = V[1]
    flag = True
    for i in range(2, n+1):
        if tmp == V[i]:
            continue
        flag = False
        break
    if flag:
        print(int(n/2))
        return

    # 奇数番目のもので、最も多い数字は？
    odd_dict = {}
    for i in range(1, n+1, 2):
        # 奇数番目のもので、最も多い数字を調べる
        if V[i] in odd_dict.keys():
            odd_dict[V[i]] += 1
            continue
        odd_dict[V[i]] = 1

    # 偶数番目のもので、最も多い数字は？
    even_dict = {}
    for i in range(2, n+1, 2):
        # 偶数番目のもので、最も多い数字を調べる
        if V[i] in even_dict.keys():
            even_dict[V[i]] += 1
            continue
        even_dict[V[i]] = 1

    sorted_odds = sorted(odd_dict.items(), key=lambda x: x[1], reverse=True)
    sorted_evens = sorted(even_dict.items(), key=lambda x: x[1], reverse=True)

    # 変換後、1種類の数字にならないように気を付ける
    if sorted_evens[0][0] == sorted_odds[0][0]:
        if len(sorted_odds) == 1:
            ans = n - sorted_odds[0][1] - sorted_evens[1][1]
        elif len(sorted_evens) == 1:
            ans = n - sorted_odds[1][1] - sorted_evens[0][1]
        else:
            ans1 = n - sorted_odds[0][1] - sorted_evens[1][1]
            ans2 = n - sorted_odds[1][1] - sorted_evens[0][1]
            ans = min(ans1, ans2)
    else:
        ans = n - sorted_evens[0][1] - sorted_odds[0][1]

    print(ans)

if __name__ == "__main__":
    solve()