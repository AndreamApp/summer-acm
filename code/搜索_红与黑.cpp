// http://icpcsummer.openjudge.cn/2018hw1/27/
/*
1. 搜索对象：设计状态
2. 搜索范围：状态转移条件
3. 扩展状态：从一个状态转移到可达的其他状态 
4. *搜索顺序 
*/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 25;

int n, m;
int cnt;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

char maze[MAX][MAX];
bool flag[MAX][MAX];
// 状态：(x, y, flag), 0<=x<=n-1, 0<=y<=m-1
// 转移：(x, y, flag) -> (nx, ny, flag') flag'[x][y] = 1
//       0<=nx<=n-1, 0<=ny<=m-1, (nx, ny)属于{(x-1, y), (x+1, y), (x, y-1), (x, y+1)}
//       flag[nx][ny] = 0, maze[nx][ny] = '.'
void dfs(int x, int y){
	cnt++;
	flag[x][y] = 1;
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(nx >= 0 && nx < n && ny >= 0 && ny < m && !flag[nx][ny] && maze[nx][ny] == '.'){
			dfs(nx, ny);
		}
	}
	// flag[x][y] = 0; 只是统计连通顶点个数，一个顶点不会再有机会被访问 
}

int main(){
//	freopen("in.txt", "r", stdin);
	while(~scanf("%d%d", &m, &n) && n && m){
		int x, y;
		for(int i = 0; i < n; i++){
			scanf("%s", maze[i]);
			for(int j = 0; j < m; j++){
				flag[i][j] = 0;
				if(maze[i][j] == '@'){
					x = i;
					y = j;
				}
			}
		}
		cnt = 0;
		dfs(x, y);
		printf("%d\n", cnt);
	}
	
	return 0;
}
