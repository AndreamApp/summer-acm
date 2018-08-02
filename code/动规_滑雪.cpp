// http://icpcsummer.openjudge.cn/2018hw1/06/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 10005;

struct point{
	int i, j, h;
	bool operator<(const point & r) const{
		return h < r.h;
	}
};

point p[MAX];
int mp[105][105];
int dp[105][105];

int main(){
	int R, C;
	scanf("%d%d", &R, &C);
	int k = 0;
	for(int i = 1; i <= R; i++){
		for(int j = 1; j <= C; j++){
			scanf("%d", &mp[i][j]);
			p[k].i = i;
			p[k].j = j;
			p[k].h = mp[i][j];
			k++;
			dp[i][j] = 1;
		}
	}
	// 将所有点从低到高排序 
	sort(p, p+R*C);
	// 从低点向高点依次更新：“我为人人”型动规 
	for(int m = 0; m < R*C; m++){
		int i = p[m].i, j = p[m].j;
		if(p[m].h < mp[i-1][j])
			dp[i-1][j] = max(dp[i-1][j], dp[i][j] + 1);
		if(p[m].h < mp[i+1][j])
			dp[i+1][j] = max(dp[i+1][j], dp[i][j] + 1);
		if(p[m].h < mp[i][j-1])
			dp[i][j-1] = max(dp[i][j-1], dp[i][j] + 1);
		if(p[m].h < mp[i][j+1])
			dp[i][j+1] = max(dp[i][j+1], dp[i][j] + 1);
	}
	
	// 最后 max(dp[i][j]) 即答案 
	int cnt = 0;
	for(int i = 1; i <= R; i++){
		for(int j = 1; j <= C; j++){
			if(dp[i][j] > cnt) cnt = dp[i][j];
		}
	}
	
	printf("%d", cnt);
	return 0;
}
