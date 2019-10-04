#-*- coding:utf-8 -*-

if __name__ == "__main__":
    Q = int(input())
    for i in range(Q):
        A, B = list(map(int, input().split()))
        x = list(range(1, A*B+1))  # 1回目の順位(使われてないもの)
        y = list(range(1, A*B+1))  # 2回目の順位（使われてないもの）
        x.remove(A)
        y.remove(B)
        ans = 0
        for n in range(A*B-1, 1, -1):
            # xとyを使ってnを作れるか？
            can_make = False
            for i in range(len(x)):
                if n%x[i] == 0:
                    syou = int(n / x[i])
                    if syou in y:
                        # OK. 作れる
                        ans += 1
                        can_make = True
                        remove_x = x[i]
                        remove_y = syou
                        break
            if can_make:
                x.remove(remove_x)
                y.remove(remove_y)
        print(ans)
