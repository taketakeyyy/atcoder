# -*- coding:utf-8 -*-

def solve():
    X = int(input())

    def f(a, b):
        return a**4+(a**3)*b+(a**2)*(b**2)+a*(b**3)+b**4

    def divisor(n):
        # nの約数を列挙する
        i = 1
        ans = []
        while i*i <= n:
            if n%i == 0:
                ans.append(i)
                if i != n//i:
                    ans.append(n//i)
            i += 1
        return ans

    # 因数分解すると、
    # A-BはXの約数であることがわかる
    ds = divisor(X)

    for d in ds:
        a = 0
        cnt = X**(1/2)+1
        while cnt > 0:
            cnt -= 1
            b = a - d
            ff = f(a,b)
            if ff == X//d:
                print(a, b)
                return
            # elif ff > X//d and b > 0:
            #     break
            a += 1

        a = 0
        cnt = X**(1/2)+1
        while cnt > 0:
            cnt -= 1
            b = a - d
            ff = f(a,b)
            if ff == X//d:
                print(a, b)
                return
            # elif ff > X//d:
            #     break
            a -= 1


if __name__ == "__main__":
    solve()
