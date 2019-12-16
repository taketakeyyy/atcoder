# -*- coding:utf-8 -*-
import math


def solve():
    a, b, x = map(int, input().split())
    rest_v = (a**2)*b - x

    # 傾けたときの直角三角形の1辺はa, もう片方をcとすると、
    # rest_v = (a*c/2)*a
    # よって、
    c = 2 * rest_v / (a**2)

    # tanθ = a/c
    tan_theta = a/c
    ans = math.degrees(math.atan(tan_theta))
    print(ans)

    return

    # 直角三角形の面積Sは、
    S = a*c/2

    # 直角三角形の3辺をそれぞれa, c, dとする
    # dの長さは三平方の定理より、
    d = (a**2 + c**2)**(1/2)

    # 求めたい角度は、dとcがなす角度θ。
    # 三角形の面積の、2辺とあいだの角度の公式より、
    # S = d*c*sinθ / 2
    # sinθのθを求めるには、逆正弦のarcsinを使って求める。
    sin_theta = (S*2)/(d*c)
    print(sin_theta)
    ans = math.degrees(math.asin(sin_theta))

    print(ans)


if __name__ == "__main__":
    solve()
