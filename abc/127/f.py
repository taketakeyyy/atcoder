# -*- coding:utf-8 -*-

def solve():
    Q = int(input())
    a_list = []
    a_count = 0
    b_sum = 0
    f = []
    
    for q in range(Q):
        query = list(input().split())
        if len(query) == 1:
            # 求値クエリ
            if a_count%2 == 0:
                # 偶数の時
                i = a_count//2 -1
            else:
                # 奇数の時
                i = a_count//2
            x = a_list[i]
            f_sum = 0
            for j in range(len(f)):
                f_sum += f[j](x)
            f_sum += b_sum

            print(x, f_sum)
            continue
        # 更新クエリ
        _, a, b = list(map(int, query))
        a_list.append(a)
        a_count += 1
        b_sum += b
        f.append(lambda x: abs(x-a))



if __name__ == "__main__":
    solve()
