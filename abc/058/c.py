# -*- coding:utf-8 -*-

"""考え方
[入力例１]
3
cbaa     # S[0]
daacc    # S[1]
acacac   # S[2]

・それぞれ文字の出現回数をカウントする
S_dic[0]["a"] = 2
S_dic[0]["b"] = 1
S_dic[0]["c"] = 1

S_dic[1]["a"] = 2
S_dic[1]["b"] = 0
S_dic[1]["c"] = 2
S_dic[1]["d"] = 1

S_dic[2]["a"] = 3
S_dic[2]["b"] = 0
S_dic[2]["c"] = 3

・全てののS[i]で共通して使える文字と、その文字数を算出する
"a" は 2個使える
"b" は 0個使える
"c" は 1個使える
"d" は 0個使える

・その算出した文字と文字数を使って、辞書順で最小の文字列を作成する。それが答え。
"aac"

"""

from collections import defaultdict

def solve():
    n = int(input())
    S_dic = [{} for i in range(n)]
    for i in range(n):
        for j in range(97, 123):
            # a~zを0に初期化
            S_dic[i][chr(j)] = 0

    for i in range(n):
        s = input()

        for moji in s:
            S_dic[i][moji] += 1
    
    usable = {}  # 使える文字と、その個数

    for j in range(97, 123):
        min_count = float("inf")
        for i in range(n):
            min_count = min(min_count, S_dic[i][chr(j)])
            if min_count == 0:
                break

        if min_count == 0:
            continue
        usable[chr(j)] = min_count

    usable_list = list(usable.items())

    usable_list.sort(key=lambda x: x[0])

    ans = ""
    for key, value in usable_list:
        ans += key * value
    
    print(ans)

    




if __name__ == "__main__":
    solve()
