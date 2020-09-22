# -*- coding: utf-8 -*-

class Info():
    def __init__(self, x, y, h):
        self.X = x
        self.Y = y
        self.H = h

def main():
    N = int(input())
    infos = []
    for i in range(N):
        x, y, h = list(map(int, input().split(" ")))
        infos.append(Info(x, y, h))
    
    # [0, 100]に座標があるのでMAXを定義する
    MAX = 100
    for posY in range(0, MAX+1):
        for posX in range(0, MAX+1):
            # 頂上がどれくらいの高さであってほしいか。
            # -1はまだよくわからないとき。0以上は確定してるとき
            # -2はだめだとわかったとき
            ans_h = -1

            for i in range(N):
                # 各座標について考える
                if infos[i].H > 0:
                    H = infos[i].H + abs(posY - infos[i].Y) + abs(posX - infos[i].X)
                    if ans_h == -1:
                        ans_h = H
                    else:
                        if ans_h != H:
                            ans_h = -2
                            break
            
            # ダメだったら別の場所を探す
            if ans_h == -2:
                continue
            
            is_ok = True
            for i in range(N):
                # 各座標について、高さが0の場合に矛盾していないか調べる
                if infos[i].H == 0:
                    if ans_h - abs(posY - infos[i].Y) - abs(posX - infos[i].X) <= 0:
                        continue
                    else:
                        is_ok = False
                        break
            
            if is_ok:
                print(posX, posY, ans_h)
                return
            

if __name__ == '__main__':
    main()
