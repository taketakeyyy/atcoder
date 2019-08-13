# -*- coding:utf-8 -*-
"""解説PDF
s1 = "abaaa" をソートして "aaaab" を得る。
s2 = "dddcc" をソートして "ccddd" を得る。
s3 = "baaaa" をソートして "aaaab" を得る。これはすでに一回現れているので答えに1を足す。
s4 = "cdddc" をソートして "ccddd" を得る。これはすでに一回現れているので答えに1を足す。
s5 = "aaaab" をソートして "aaaab" を得る。これはすでに二回現れているので答えに2を足す。

というふうにやる。

「これはすでにK回現れているので」は、ハッシュテーブルでやればよい

"""
def solve():
    N = int(input())
    d = {}
    for i in range(N):
        s = "".join(sorted(input()))
        if not s in d:
            d[s] = 0
        d[s] += 1

    ans = 0
    for s, value in d.items():
        if value >= 2:
            # 和の公式で答えにタス
            ans += (value-1+1)*(value-1)/2
    print(int(ans))


if __name__ == "__main__":
    solve()
