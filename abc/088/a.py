#-*- coding:utf-8 -*-

if __name__ == "__main__":
    N = int(input())
    A = int(input())
    # 500円玉無限枚なので、Nを500で割った余りが1円玉で払えるかを考える
    if (N%500) <= A:
        print("Yes")
    else:
        print("No")
