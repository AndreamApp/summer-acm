#include <bits/stdc++.h>

using namespace std;

const int MAX = 105;
const int inf = 0x3f3f3f3f;

int n;

struct Edge{
	int v;
	int w;
};

struct Point{
	int v;
	int dis;
	bool operator<(const Point & d) const{
		return dis > d.dis;
	}
	Point(int V, int Dis) : v(V), dis(Dis){
	}
};

int G[MAX][MAX];

int d[MAX];
bool used[MAX];

int prim(int s){
	int totalWeight = 0;
	memset(d, inf, sizeof d);
	memset(used, 0, sizeof used);
	d[s] = 0;
	// 起始状态 
	Point p(s, 0);
	priority_queue<Point> q;
	q.push(p);
	while(q.size()){
		// 找到下一个不在生成树中的*最近*结点
		do{
			p = q.top(); q.pop();
		} while(used[p.v] && q.size());
		int u = p.v;
		if(!used[u]){ 
			used[u] = 1;
			totalWeight += p.dis; // 那个最近的结点，就是最小生成树的一个结点 
			// 计算生成树到相邻结点的最短距离 
			for(int j = 0; j < n; j++){
				if(!used[j]){
					if(d[j] > G[u][j]){ 
//						d[j] = d[u] + G[u][j];
						d[j] = G[u][j]; // Dijkstra的d[j]保存起点s到j的最短距离，而Prim的d[j]保存的是生成树到j的最短距离 
						q.push(Point(j, d[j])); // 更新的同时加入队列，保证最近的结点能被找到 
					}
				}
			}
		}
	}
	return totalWeight;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &G[i][j]);
			}
		}
		printf("%d\n", prim(0));
	}
	return 0; 
} 
