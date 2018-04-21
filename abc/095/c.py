if __name__ == "__main__":
    A, B, C, X, Y = list(map(int, input().split()))
    ans = 0
    if (A + B) >= 2*C:
        # ABピザ2枚買ってAとBに分けた方がお得
        if (A >= B):
            if (B >= 2*C):
                # 全部ABの方がお得
                if X >= Y:
                    ans += (2*C) * X
                    print(ans)
                    exit()
                else:
                    ans += (2*C) * Y
                    print(ans)
                    exit()
            elif (A >= 2*C):
                # Aの分はABピザで買ったほうがお得
                ans += (2*C) * X
                if Y >= X:
                    ans += A * (Y - X)
                print(ans)
                exit()
            else:
                # 枚数が少ない方をABで買う
                if X >= Y:
                    ans += (2*C) * Y
                    ans += A * (X - Y)
                else:
                    ans += (2*C) * X
                    ans += B * (Y - X)
                print(ans)
                exit()
        else:
            if (A >= 2*C):
                if X >= Y:
                    # 全部ABの方がお得
                    ans += (2*C) * X
                    print(ans)
                    exit()
                else:
                    # 全部ABの方がお得
                    ans += (2*C) * Y
                    print(ans)
                    exit()
            elif (B >= 2*C):
                # Bの分はABピザで買ったほうがお得
                ans += (2*C) * Y
                if X >= Y:
                    ans += A * (X - Y)
                print(ans)
                exit()
            else:
                # 枚数が少ない方をABで買う
                if X >= Y:
                    ans += (2*C) * Y
                    ans += A * (X - Y)
                else:
                    ans += (2*C) * X
                    ans += B * (Y - X)
                print(ans)
                exit()
    else:
        # 普通に買ったほうがよい
        ans += A * X + B * Y
        print(ans)
        exit()
