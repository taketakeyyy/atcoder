# -*- coding:utf-8 -*-
import math

if __name__ == '__main__':
    a, b = input().split()
    str = a+b
    num = int(str)
    if math.sqrt(num).is_integer():
        print("Yes")
    else:
        print("No")
