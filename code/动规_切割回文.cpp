#include <bits/stdc++.h>

using namespace std;

const int MAX = 1005;

char s[MAX];

bool re[MAX][MAX];
int dp[MAX]; 

/*
 状态1： 
 re[i][j] 表示 s[i,j]是否是回文串
 re[i][j] = 1, j - i == 0
          = s[i] == s[j], j - i == 1
 re[i][j] = re[i+1][j-1] & s[i] == s[j]
 O(n^2)

 状态2： 
 dp[i][j] 表示 s[i,j]切割为回文串最少切割次数, 0<=i<=j<=n-1，求dp[0][n-1] 
 dp[i][j] = 0, j - i == 0
          = s[i] != s[j], j - i == 1
 dp[i][j] = min(dp[i][k] + dp[k][j]) + 1, i<k<j
 O(n^3)
 
 状态3： 
 dp[i] 表示 s[0,i]切割为回文串最少切割次数, 0<=i<=n-1，求dp[n-1] 
 dp[i] = 0, if(re[0][i])
 dp[i] = dp[k] + 1, if(re[k+1][i]), 0<=k<i
 O(n^2)
*/


int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s", s);
		int n = strlen(s);
		
		for(int i = 0; i < n; i++){
			re[i][i] = 1;
			if(i != n-1)
				re[i][i+1] = s[i] == s[i+1];
		}
		
		for(int l = 3; l <= n; l++){
			for(int i = 0; i + l - 1 < n; i++){
				int j = i + l - 1;
				re[i][j] = re[i+1][j-1] && s[i] == s[j];
			}
		}
		
		/* 使用状态2，O(n^3) 超时，实际上只需要计算dp[0][j]的值就可以，简化为状态3 
		for(int i = 0; i < n; i++){
			dp[i][i] = 0;
			if(i != n-1)
				dp[i][i+1] = s[i] != s[i+1];
		}
		dp[n-1][n-1] = 0;
		
		for(int i = n-2; i >= 0; i--){
			for(int j = i+2; j < n; j++){
				if(re[i][j]) dp[i][j] = 0;
				else{
					int m = 1 << 30;
					for(int k = i; k < j; k++){
						m = min(m, dp[i][k] + dp[k+1][j]);
					}
					dp[i][j] = m + 1;
				}
			}
		}
		printf("%d\n", dp[0][n-1]);
		*/
		
		for(int i = 0; i < n; i++){
			if(re[0][i]) dp[i] = 0;
			else{
				for(int k = 0; k < i; k++){
					if(re[k+1][i]){
						dp[i] = dp[k] + 1;
						break;
					}
				}
			}
		}
		
		printf("%d\n", dp[n-1]);
	}
	return 0;
}
