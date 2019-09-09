n,k=map(int,input().split())
s=[int(input()) for i in range(n)]

ans=lt=0
val=1
if 0 in s:
  ans=n
else:
  for rt in range(n):
    val*=s[rt]
    if val<=k:
      ans=max(ans,rt-lt+1)
    else:
      val/=s[lt]
      lt+=1
 
print(ans)