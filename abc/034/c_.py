# https://atcoder.jp/contests/abc034/submissions/7332771
w,h=map(int,input().split())

def cmb(n,r,mod=10**9+7):
    fac=[1,1]
    for i in range(2,n+1):
        fac.append(fac[i-1]*i%mod)
    ret=fac[n]*pow(fac[r]*fac[n-r]%mod,mod-2,mod)%mod
    return ret

n=w+h-2
r=min(w,h)-1
print(cmb(n,r))
