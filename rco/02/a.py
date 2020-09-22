#-*- coding:utf-8 -*-

if __name__ == "__main__":
    N, K = list(map(int, input().split()))
    for i in range(K):
        a, b, c, d = list(map(int, input().split()))
        #SからGへ移動するx方向とy方向は、
        # 幅優先探索をして、
        # (1) 到達できるならば、道中を壁に変える
        # (2) 到達できないならば、最も遠い経路の壁を空に変える
        x = c - a
        y = d - b
        print()
