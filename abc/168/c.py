# -*- coding:utf-8 -*-

def solve():
    import sys
    import math

    A, B, H, M = list(map(int, sys.stdin.readline().split()))

    h_speed = 360 / (12*60)
    m_speed = 360 / 60

    m = H*60 + M

    h_angle = h_speed * m
    m_angle = m_speed * m % 360
    angle = abs(h_angle - m_angle) if abs(h_angle-m_angle) <= 180 else 360 - abs(h_angle-m_angle)

    if angle == 0:
        print(abs(A-B))
        return
    elif angle == 180:
        print(A+B)
        return

    # 余弦定理
    C = (B**2 + A**2 - 2*A*B*math.cos(math.radians(angle)))**(1/2)
    print(C)

if __name__ == "__main__":
    solve()
