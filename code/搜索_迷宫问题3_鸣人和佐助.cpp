// http://icpcsummer.openjudge.cn/2018hw1/23/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 205;

int n, m, t;
int endx, endy;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

struct point{
	int x, y, steps;
	int ckl;
	point(int X, int Y, int Steps, int Ckl)
		: x(X), y(Y), steps(Steps), ckl(Ckl){
	}
};

char maze[MAX][MAX];
bool flag[MAX][MAX][10];
/*
 状态：point(x, y, step, ckl), 0<=x<=n-1, 0<=y<=m-1, maze[x][y]='*'or'#'  (flag也算状态的一部分，但是省略了)
 转移：(x, y, step, ckl) -> (nx, ny, step+1, ckl), maze[nx][ny] = '*', flag[nx][ny] = 0 
       (x, y, step, ckl) -> (nx, ny, step+1, ckl-1), maze[nx][ny] = '#', ckl > 0, flag[nx][ny] = 0 
       (nx, ny)属于{(x-1, y), (x+1, y), (x, y-1), (x, y+1)}
       
*/
int bfs(int x, int y, int ckl){
	// 状态起点 
	queue<point> q;
	q.push(point(x, y, 0, ckl));
	flag[x][y][ckl] = 1;
	while(q.size()){
		// 特判：状态终点 
		point p = q.front(); q.pop();
//		printf("visit (%d, %d), steps = %d\n", p.x, p.y, p.steps);
		if(p.x == endx && p.y == endy){
			return p.steps;
		}
		// 遍历可达状态 
		for(int i = 0; i < 4; i++){
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m){
				// 状态转移 
				if('*' == maze[nx][ny] && !flag[nx][ny][p.ckl]){
					flag[nx][ny][p.ckl] = 1;
					q.push(point(nx, ny, p.steps + 1, p.ckl));
				}
				else if('#' == maze[nx][ny] && p.ckl > 0 && !flag[nx][ny][p.ckl-1]){
					flag[nx][ny][p.ckl-1] = 1;
					q.push(point(nx, ny, p.steps + 1, p.ckl - 1));
				}
				/* 分类讨论要清晰，不重复也不遗漏 
				int steps = p.steps;
				int ckl = p.ckl;
				// 状态转移 
				if('*' == maze[nx][ny]){
					steps++;
				}
				else if('#' == maze[nx][ny]){
					if(ckl > 0){
						steps++;
						ckl--;
					}
					else{
						continue;
					}
				}
				if(!flag[nx][ny][ckl]){
					flag[nx][ny][ckl] = 1;
					q.push(point(nx, ny, steps, ckl));
				}
				*/
//				printf("push (%d, %d), steps = %d, kill = %d\n", nx, ny, steps, kill);
			}
		}
	}
	return -1;
}

int main(){
//	freopen("in.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &t);
	int x, y;
	for(int i = 0; i < n; i++){
		scanf("%s", maze[i]);
		for(int j = 0; j < m; j++){
			// prepare for bfs
			for(int k = 0; k <= t; k++)
				flag[i][j][k] = 0;
			if(maze[i][j] == '@'){
				maze[i][j] = '*';
				x = i;
				y = j;
			}
			else if(maze[i][j] == '+'){
				maze[i][j] = '*';
				endx = i;
				endy = j;
			}
		}
	}
	int res = bfs(x, y, t);
	printf("%d", res);
	return 0;
}
