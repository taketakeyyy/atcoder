# -*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    Cs = []
    Ss = []
    Fs = []
    for i in range(N-1):
        C, S, F = list(map(int, input().split()))
        Cs.append(C)
        Ss.append(S)
        Fs.append(F)

    for i in range(N-1):
        ans = 0
        for j in range(i, N-1):
            if ans <= Ss[j]:
                # 駅の最初の出発時間になっていないなら待つ
                ans = Ss[j] + Cs[j]
            else:
                # 最初の出発時間はすでに過ぎているならば
                if (ans - Ss[j]) % Fs[j] == 0:
                    # すぐに出発できる
                    ans += Cs[j]
                else:
                    # 出発時間まで待つ
                    ans += Cs[j] + Fs[j] - (ans - Ss[j]) % Fs[j]
        print(ans)
    print(0)
