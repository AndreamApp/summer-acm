// http://icpcsummer.openjudge.cn/2018hw1/24/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 205;

int n, m;
int endx, endy;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

struct point{
	int x, y, steps;
	bool kill;
	point(int X, int Y, int Steps, bool Kill)
		: x(X), y(Y), steps(Steps), kill(Kill){
	}
//	bool operator<(const point & p) const{
//		return steps < p.steps;
//	}
};

char maze[MAX][MAX];
bool flag[MAX][MAX];
/*
 状态：point(x, y, step, kill), 0<=x<=n-1, 0<=y<=m-1, maze[x][y]='@'or'x'  (flag也算状态的一部分，但是省略了)
 转移：(x, y, step, 0) -> (nx, ny, step+1, 0), maze[nx][ny] = '@'
       (x, y, step, 0) -> (nx, ny, step+1, 1), maze[nx][ny] = 'x'
       (x, y, step, 1) -> (x, y, step+1, 0), maze[x][y] = 'x'
       (nx, ny)属于{(x-1, y), (x+1, y), (x, y-1), (x, y+1)}
       flag[nx][ny] = 0 
*/
int bfs(int x, int y){
	// 状态起点 
	queue<point> q;
	q.push(point(x, y, 0, 0));
	flag[x][y] = 1;
	while(q.size()){
		// 特判：状态终点 
		point p = q.front(); q.pop();
//		printf("visit (%d, %d), steps = %d\n", p.x, p.y, p.steps);
		if(p.x == endx && p.y == endy){
			return p.steps;
		}
		// 遍历可达状态 
		if(p.kill){
			p.steps++;
			p.kill = 0;
			q.push(p);
//			printf("push (%d, %d), steps = %d, kill = %d\n", p.x, p.y, p.steps, p.kill);
		}
		else{
			for(int i = 0; i < 4; i++){
				int nx = p.x + dx[i];
				int ny = p.y + dy[i];
				if(nx >= 0 && nx < n && ny >= 0 && ny < m && !flag[nx][ny] && maze[nx][ny] != '#'){
					bool kill = 0;
					int steps = p.steps;
					// 状态转移 
					if('@' == maze[nx][ny]){
						steps++;
					}
					else if('x' == maze[nx][ny]){
						kill = 1;
						steps++;
					}
					flag[nx][ny] = 1;
					q.push(point(nx, ny, steps, kill));
//					printf("push (%d, %d), steps = %d, kill = %d\n", nx, ny, steps, kill);
				}
			}
		}
	}
	return -1;
}

int main(){
//	freopen("in.txt", "r", stdin);
	int S;
	scanf("%d", &S);
	while(S--){
		scanf("%d%d", &n, &m);
		int x, y;
		for(int i = 0; i < n; i++){
			scanf("%s", maze[i]);
			for(int j = 0; j < m; j++){
				flag[i][j] = 0; // prepare for bfs
				if(maze[i][j] == 'r'){
					maze[i][j] = '@';
					x = i;
					y = j;
				}
				else if(maze[i][j] == 'a'){
					maze[i][j] = '@';
					endx = i;
					endy = j;
				}
			}
		}
		int res = bfs(x, y);
		if(res == -1)
			printf("Impossible\n");
		else
			printf("%d\n", res);
	}
	return 0;
}
