// http://icpcsummer.openjudge.cn/2018hw1/12/
/*
状态：dp[j] 表示前i个数里挑凑成j的方案数，1<=i<=n，1<=j<=x
条件：dp[0] = 1 
方程：dp[j] = dp[j] + dp[j-a[i]], 1<=i<=n, x>=j>=a[i] (j-a[i] >= 0)
复杂度：O(nx)  空间复杂度：O(x)
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring> 

using namespace std;

const int MAXN = 405;

char s1[MAXN], s2[MAXN], s[MAXN];
int l1, l2, l;
bool dp[MAXN];

int main(){
//	freopen("in.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		scanf("%s%s%s", s1+1, s2+1, s+1);
		l1 = strlen(s1+1);
		l2 = strlen(s2+1);
		l = strlen(s+1);
		//memset(dp, 0, sizeof(bool) * (l+1));
		dp[0] = s2[1] == s[1];
		dp[1] = s1[1] == s[1];
		for(int i = 2; i <= l; i++){
			for(int j = i; j >= 0; j--){
				dp[j] = (j >= 1 && dp[j-1] && s1[j] == s[i]) || (dp[j] && s2[i-j] == s[i]);
			}
		}
		bool res = false;
		for(int j = 0; j <= l; j++){
			if(dp[j]) {
				res = true;
				break;
			}
		}
		printf("Data set %d: %s\n", t, res ? "yes" : "no");
	}
	return 0;
}
