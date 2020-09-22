# -*- coding:utf-8 -*-

"""解説
解説PDFを実装

考察問題。

与えられた文字列が
　L R L R R L

のとき、問題を単純化するため、左端にR、右端にLがあるものとする

(R) L R L R R L (L)

このとき、

・互いが向き合っている箇所（RL）を赤丸
・互いが反対方向を向いている箇所（LR）を青丸とする

赤丸と青丸を選んで操作をすれば、幸福な人を2人増やすことができる。ということに気づく必要がある

ただし、左端か右端を選んで操作をした場合、幸福な人は1人しか増やせない。

この性質を利用して、最大数を求める。


（入力例１）
i:  0  1 2 3 4 5 6  7
S: (R) L R L R R L (L) ... 幸福な人: 1人, RLの数: 3, LRの数: 2

1回目の操作で l=2, r=5 を選ぶと

i:  0  1 2 3 4 5 6  7
S: (R) L L L R L L (L) ... 幸福な人: 3人, RLの数: 2, LRの数: 1

もしもう一度操作できるなら、l=4, r=4 を選ぶと

i:  0  1 2 3 4 5 6  7
S: (R) L L L L L L (L) ... 幸福な人: 5人, RLの数: 1, LRの数: 0

もしこれ以上操作できたとしても、RLとLRの組は見つけることができないので、これ以上幸福な人を増やすことはできない

1回操作する毎に、RLの数とLRの数は1ずつ減る。なるべく左端または右端を選ばないように操作することで最大化することができる。

RLの数とLRの数は線形探索すればO(N)で数えることができる。
初期状態の幸福な人の数も線形探索でO(N)で調べることができる。

よってO(N)で答えを出せそうである。

"""


def solve():
    N, K = list(map(int, input().split()))
    S = input()
    S = "R" + S + "L"

    endRL = 0  # 端っこのRL
    RL, LR = 0, 0  # RLの数, LRの数
    happy_num = 0  # 幸福な人の数

    M = len(S)
    for i in range(1, M):
        if S[i-1]=="R" and S[i]=="L":
            if (i-1)==0 or i==(M-1):
                endRL += 1
            else:
                RL += 1
        elif S[i-1]=="L" and S[i]=="R":
            LR += 1

        # 初期状態の幸福な人の数を数える
        if (i-1)==0 or i==(M-1):
            continue
        if (S[i-1]=="L" and S[i]=="L") or (S[i-1]=="R" and S[i]=="R"):
            happy_num += 1

    # 幸福な人の数を可能な限り最大化する
    if RL >= LR:
        if K >= LR:
            happy_num += LR*2
            RL -= LR
            K -= LR
        else:
            happy_num += K*2
    else:
        if K >= RL:
            happy_num += RL*2
            LR -= RL
            K -= RL
            if K >= min(LR, endRL):
                happy_num += min(LR, endRL)
            else:
                happy_num += K
        else:
            happy_num += K*2

    print(happy_num)


"""別解
解説動画でやってること。

考察問題。

ランレングス法みたいな考え方をする。

LグループとRグループに分けて考える。

LグループとRグループの境目を選択して操作をすると、基本的に幸福な人の数を＋２できる

ただし、端っこの境目を選んだときのみ、＋１になる。


・入力例２を考える

## 初期状態
 L R R L R L R R L R L L R
   .         .         .     幸福な人：3人


## LグループとRグループの境目を選択して、操作をする

 L R R L R L R R L R L L R
  |___|

 L L L L R L R R L R L L R
   . . .     .         .     幸福な人：5人

## LグループとRグループの境目を選択して、操作をする

 L L L L R L R R L R L L R
        |_|

 L L L L L L R R L R L L R
   . . . . . .         .     幸福な人：7人

## LグループとRグループの境目を選択して、操作をする

 L L L L L L R R L R L L R
            |___|

 L L L L L L L L L R L L R
   . . . . . . . .     .     幸福な人：9人

## LグループとRグループの境目を選択して、操作をする

 L L L L L L L L L R L L R
                  |_|

 L L L L L L L L L L L L R
   . . . . . . . . . . .     幸福な人：11人

## LグループとRグループの境目を選択して、操作をする

 L L L L L L L L L L L L R
                        |_|

 L L L L L L L L L L L L L
   . . . . . . . . . . . .   幸福な人：12人


この考察からすると、初期状態の幸福な人の数を score とすると、

・K回操作して、初期状態の幸福な人に加えて 2*K 人を幸福にすることができたパターン = score + 2*K
・K回以下の操作で、すべての人を L(R) にすることができたパターン = N-1

のどちらかなので、最終的な幸福な人の数 ans は、

ans = min(score+2*K, N-1)

となる。

初期状態の幸福な人の数 score をO(N)で数えればよいだけなので、計算量はO(N)

"""
def solve2():
    N, K = list(map(int, input().split()))
    S = input()

    ans = 0
    for i in range(N-1):
        if S[i] == S[i+1]:
            ans += 1

    ans = min(ans + 2*K, N-1)
    print(ans)


if __name__ == "__main__":
    solve()
