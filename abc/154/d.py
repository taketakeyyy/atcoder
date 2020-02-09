# -*- coding:utf-8 -*-

def solve():
    N, K = list(map(int, input().split()))
    Ps = list(map(int, input().split()))

    kitai = []  # kitai[i] := p[i]の期待値
    for p in Ps:
        kitai.append(((1+p)*p/2)*(1/p))

    # 尺取法でさがすぜ
    # まずは初期状態を計算する
    ans = 0
    for i in range(0, K):
        ans += kitai[i]

    # つぎにしゃくとっていくぜ
    total = ans
    for i in range(K, N):
        total = total + kitai[i] - kitai[i-K]
        if total > ans:
            ans = total

    print(ans)

if __name__ == "__main__":
    solve()
