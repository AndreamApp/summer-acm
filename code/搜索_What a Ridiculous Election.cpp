// http://icpcsummer.openjudge.cn/2018hw1/26/
#include <bits/stdc++.h>
#include <map>

using namespace std;

map<string, int> res;

void dfs(string s, int op2, int op3, int steps){
//	cout << "dfs:" << s << endl;
	if(res.count(s)){
		if(steps >= res[s]){ // 最优性剪枝 
			return;
		}
		else{
			res[s] = steps;
		}
	}
	else{
		res[s] = steps;
	}
	string s2;
	for(int i = 0; i < 4; i++){
		s2 = s;
		swap(s2[i], s2[i+1]);
		dfs(s2, op2, op3, steps+1);
	}
	if(op2 > 0){
		for(int i = 0; i < 5; i++){
			s2 = s;
			s2[i] = (s2[i] - '0' + 1) % 10 + '0';
			dfs(s2, op2-1, op3, steps+1);
		}
	}
	if(op3 > 0){
		for(int i = 0; i < 5; i++){
			s2 = s;
			s2[i] = ((s2[i] - '0') * 2) % 10 + '0';
//			cout << s << " -> " << s2 << endl;
			dfs(s2, op2, op3-1, steps+1);
		}
	}
}

/*
思路1：对每一个样例，bfs搜索(s, op2, op3)至12345，得到最短路径 
优点：对单个样例速度快。但样例数太多，不如用一次深度优先搜索遍历所有状态，把结果保存下来 
*/
int main(){
	ios::sync_with_stdio(false);
	dfs("12345", 3, 2, 0);
	string s;
	while(cin >> s){
		if(res.count(s)){
			cout << res[s] << endl;
		}
		else{
			cout << -1 << endl;
		}
	}
	return 0;
}
