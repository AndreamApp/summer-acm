// http://icpcsummer.openjudge.cn/2018hw1/23/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 105;

int n, m;
int endx, endy;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

struct point{
	int x, y, steps;
	char key; // 手里的钥匙数 
	char layout; // 场上守卫的情况 
	bool kill;
};

int S; // 守卫数量 
char s[MAX][MAX]; // 守卫下标 
char maze[MAX][MAX];
bool flag[MAX][MAX][10][33]; // 0 <= lauout < 32
/*
 状态：point(x, y, steps, key, layout, kill), 0<=x<=n-1, 0<=y<=n-1, 0<=key<=9, 0<=layout<32, 0<=kill<=1, maze[x][y]='.'or'#'or'S'or'%d'  (flag也算状态的一部分，但是省略了)
 转移：(x, y, steps, key, layout, 0) -> (nx, ny, steps+1, key, layout, 0), maze[nx][ny] = '.', flag[nx][ny][key][layout] = 0 
       (x, y, steps, key, layout, 0) -> (nx, ny, steps+1, key, layout, 1), maze[nx][ny] = 'S', flag[nx][ny][key][layout] = 0
       (x, y, steps, key, layout, 1) -> (x, y, steps+1, key, layout&~(1<<s[x][y]), 0), s是maze[x][y]这个守卫的下标 
       (x, y, steps, key, layout, 0) -> (nx, ny, steps+1, key+1, layout, 1), maze[nx][ny] = key+1+'0', flag[nx][ny][key][layout] = 0
       (nx, ny)属于{(x-1, y), (x+1, y), (x, y-1), (x, y+1)}
 初始：(x, y, 0, 0, (1<<S)-1, 0), S为守卫总数 
 终止：(endx, endy, steps, m, layout, 0) , steps即为答案，如果达不到终止状态即无解 
*/
int bfs(int x, int y, int m){
	// 状态起点 
	queue<point> q;
	q.push(point{x, y, 0, 0, (1<<S)-1, 0});
	flag[x][y][0][(1<<S)-1] = 1;
	while(q.size()){
		// 特判：状态终点 
		point p = q.front(); q.pop();
//		printf("visit (%d, %d), steps=%d, key=%d, layout=%d, kill=%d\n", p.x, p.y, p.steps, p.key, p.layout, p.kill);
		if(p.x == endx && p.y == endy && p.key == m){
			return p.steps;
		}
		// 遍历可达状态 
		if(p.kill){
			p.steps++;
			p.layout &= ~(1<<s[p.x][p.y]);
			p.kill = 0;
			q.push(p);
		}
		else{
			for(int i = 0; i < 4; i++){
				int nx = p.x + dx[i];
				int ny = p.y + dy[i];
				if(nx >= 0 && nx < n && ny >= 0 && ny < n){
					// 状态转移 
					// 拿不到的钥匙或者杀死过的守卫可以直接走  
					bool gothrough = maze[nx][ny] == '.'
								 || maze[nx][ny] >= '1' && maze[nx][ny] <= '9' && maze[nx][ny] != p.key+1+'0'
								 || (maze[nx][ny] == 'S' && (p.layout&(1<<s[nx][ny])) == 0);
					if(gothrough && !flag[nx][ny][p.key][p.layout]){
						flag[nx][ny][p.key][p.layout] = 1;
						q.push(point{nx, ny, p.steps+1, p.key, p.layout, 0});
					}
					// 'S' == maze[nx][ny] && (p.layout&(1<<s[nx][ny])) 表示(nx, ny)在当前场面上有守卫 
					else if('S' == maze[nx][ny] && (p.layout&(1<<s[nx][ny])) && !flag[nx][ny][p.key][p.layout]){
						flag[nx][ny][p.key][p.layout] = 1;
						q.push(point{nx, ny, p.steps+1, p.key, p.layout, 1});
					}
					else if(maze[nx][ny] == p.key+1+'0' && !flag[nx][ny][p.key+1][p.layout]){
						flag[nx][ny][p.key+1][p.layout] = 1;
						q.push(point{nx, ny, p.steps+1, p.key+1, p.layout, 0});
					}
					else{
						continue;
					}
//					printf("push (%d, %d), steps=%d, key=%d, layout=%d, kill=%d\n", p.x, p.y, p.steps, p.key, p.layout, p.kill);
				}
			}
		}
	}
	return -1;
}

int main(){
//	freopen("in.txt", "r", stdin);
	// 注意只有n=0且m=0才停止，有可能n!=0但是m=0 
	while(~scanf("%d%d", &n, &m) && (n != 0 || m != 0)){
		S = 0;
		int x, y;
		
		for(int i = 0; i < n; i++){
			scanf("%s", maze[i]);
			for(int j = 0; j < n; j++){
				// prepare for bfs
				memset(&flag[i][j], 0, sizeof(bool) * (10*33));
				if('K' == maze[i][j]){
					maze[i][j] = '.';
					x = i;
					y = j;
				}
				else if('T' == maze[i][j]){
					maze[i][j] = '.';
					endx = i;
					endy = j;
				}
				else if('S' == maze[i][j]){
					s[i][j] = S++; // 记录守卫下标 
				}
			}
		}
		int res = bfs(x, y, m);
		if(res == -1) printf("impossible\n");
		else printf("%d\n", res);
	}
	return 0;
}
