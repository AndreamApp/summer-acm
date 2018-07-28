// http://icpcsummer.openjudge.cn/2018hw1/24/
#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int MAX = 205;

int n, m;
int endx, endy;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

struct point{
	int x, y, steps;
	bool operator<(const point & p) const{
		return steps < p.steps;
	}
};

int d[MAX][MAX];
char maze[MAX][MAX];
bool flag[MAX][MAX];
// 状态：point(x, y, step), 0<=x<=n-1, 0<=y<=m-1
// 转移：(x, y, step) -> (nx, ny, step+1), maze[nx][ny] = '@'
//                    -> (nx, ny, step+2), maze[nx][ny] = 'x'
//       0<=nx<=n-1, 0<=ny<=m-1, (nx, ny)属于{(x-1, y), (x+1, y), (x, y-1), (x, y+1)}
//       flag[nx][ny] = 0 
int bfs(int x, int y){
	int res = 1 << 30;
	// 状态起点 
	priority_queue<point> q;
	q.push(point{x, y, 0});
	flag[x][y] = 1;
	while(q.size()){
		// 特判：状态终点 
		point p = q.top(); q.pop();
		printf("visit (%d, %d), steps = %d\n", p.x, p.y, p.steps);
		if(p.x == endx && p.y == endy){
			if(p.steps < res) res = p.steps;
		}
		// 遍历可达状态 
		for(int i = 0; i < 4; i++){
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m){
				int steps = p.steps;
				// 状态转移 
				if('@' == maze[nx][ny] || 'a' == maze[nx][ny]){
					steps++;
				}
				else if('x' == maze[nx][ny]){
					steps+=2;
				}
				else{
					continue;
				}
				if(steps < d[nx][ny]){
					d[nx][ny] = steps;
					q.push(point{nx, ny, d[nx][ny]});
				}
//				printf("push (%d, %d), steps = %d\n", nx, ny, steps);
			}
		}
	}
	return res == 1 << 30 ? -1 : res;
}

int main(){
	freopen("in.txt", "r", stdin);
	int S;
	scanf("%d", &S);
	while(S--){
		scanf("%d%d", &n, &m);
		int x, y;
		for(int i = 0; i < n; i++){
			scanf("%s", maze[i]);
			for(int j = 0; j < m; j++){
				flag[i][j] = 0; // prepare for bfs
				d[i][j] = 1 << 30;
				if(maze[i][j] == 'r'){
					x = i;
					y = j;
				}
				else if(maze[i][j] == 'a'){
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
