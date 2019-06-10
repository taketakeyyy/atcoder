L = list(input())
n = len(L)
mod = 10**9+7
 
dp = [[0]*2 for i in range(n+1)]
dp[0][0] = 1
 
for i,c in enumerate(L):
    if c == '1':
        dp[i+1][0] = dp[i][0]*2%mod
        dp[i+1][1] = (dp[i][0]+dp[i][1]*3)%mod
    else:
        dp[i+1][0] = dp[i][0]%mod
        dp[i+1][1] = dp[i][1]*3%mod
print(sum(dp[-1])%mod)
