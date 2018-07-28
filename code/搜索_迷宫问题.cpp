// http://icpcsummer.openjudge.cn/2018hw1/21/
#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <vector>

using namespace std;

const int n = 5;

struct point{
	int x, y;
	bool operator<(const point & p) const{
		if(x == p.x) return y < p.y;
		return x < p.x;
	}
};

int maze[n+2][n+2]; 
int len;
vector<point> path;
int minLen = 1 << 30;
vector<point> minPath;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

void dfs(int x, int y){
	maze[x][y] = 1;
	path.push_back(point{x, y});
//	printf("visit (%d, %d) len=%d\n", x, y, len);
	if(x == 5 && y == 5){
		if(len < minLen){
			minLen = len;
			minPath.assign(path.begin(), path.end());
		}
	}
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(nx >= 1 && nx <= 5 && ny >= 1 && ny <= 5 && maze[nx][ny] == 0){
			len++;
			dfs(nx, ny);
			len--;
		}
	}
	path.pop_back();
	maze[x][y] = 0;
}

int main(){
//	freopen("in.txt", "r", stdin);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &maze[i][j]);
		}
	}
	dfs(1, 1);
	sort(minPath.begin(), minPath.end());
	for(int i = 0; i < minPath.size(); i++){
		printf("(%d, %d)\n", minPath[i].x-1, minPath[i].y-1);
	}
	return 0;
}
