#include <bits/stdc++.h>

using namespace std;

int chess[8][8];

bool resolve;
int symbol;
char path[1000000];
char res[1000000];
int len;

int h(){
	int stat[4] = {0};
	stat[chess[2][2]]++; stat[chess[2][3]]++; stat[chess[2][4]]++; 
	stat[chess[3][2]]++;                      stat[chess[3][4]]++; 
	stat[chess[4][2]]++; stat[chess[4][3]]++; stat[chess[4][4]]++;
	sort(stat, stat+4);
	return 8 - stat[3]; 
}

void moveA(){
	chess[7][2] = chess[0][2];
	for(int i = 1; i <= 7; i++)
		chess[i-1][2] = chess[i][2];
}

void moveF(){
	for(int i = 6; i >= 0; i--)
		chess[i+1][2] = chess[i][2];
	chess[0][2] = chess[7][2];
}

void moveB(){
	chess[7][4] = chess[0][4];
	for(int i = 1; i <= 7; i++)
		chess[i-1][4] = chess[i][4];
}

void moveE(){
	for(int i = 6; i >= 0; i--)
		chess[i+1][4] = chess[i][4];
	chess[0][4] = chess[7][4];
}

void moveC(){
	for(int i = 6; i >= 0; i--)
		chess[2][i+1] = chess[2][i];
	chess[2][0] = chess[2][7];
}

void moveH(){
	chess[2][7] = chess[2][0];
	for(int i = 1; i <= 7; i++)
		chess[2][i-1] = chess[2][i];
}

void moveD(){
	for(int i = 6; i >= 0; i--)
		chess[4][i+1] = chess[4][i];
	chess[4][0] = chess[4][7];
}

void moveG(){
	chess[4][7] = chess[4][0];
	for(int i = 1; i <= 7; i++)
		chess[4][i-1] = chess[4][i];
}


void dfs(int depth){
	if(resolve) return;
	int eval = h();
	if(eval == 0) {
		resolve = 1;
		symbol = chess[2][2];
		path[len] = 0;
		strcpy(res, path);
		return;
	}
	if(depth < eval) return; 
	path[len++]='A';  moveA();  dfs(depth - 1);  moveF();  len--;
	path[len++]='B';  moveB();  dfs(depth - 1);  moveE();  len--;
	path[len++]='C';  moveC();  dfs(depth - 1);  moveH();  len--;
	path[len++]='D';  moveD();  dfs(depth - 1);  moveG();  len--;
	path[len++]='E';  moveE();  dfs(depth - 1);  moveB();  len--;
	path[len++]='F';  moveF();  dfs(depth - 1);  moveA();  len--;
	path[len++]='G';  moveG();  dfs(depth - 1);  moveD();  len--;
	path[len++]='H';  moveH();  dfs(depth - 1);  moveC();  len--;
}

int solve(){
	int depth = 0;
	while(1){
		dfs(depth);
		if(resolve) break;
		depth++;
	}
	return depth;
}

int main(){
	while(~scanf("%d", &chess[0][2]) && chess[0][2]){
		scanf("%d%d%d", &chess[0][4], &chess[1][2], &chess[1][4]);
		for(int i = 0; i < 7; i++){
			scanf("%d", &chess[2][i]);
		}
		scanf("%d%d", &chess[3][2], &chess[3][4]);
		for(int i = 0; i < 7; i++){
			scanf("%d", &chess[4][i]);
		}
		scanf("%d%d%d%d", &chess[5][2], &chess[5][4], &chess[6][2], &chess[6][4]);
		
		resolve = false;
		len = 0;
		int step = solve();
		printf("%s\n%d\n", step == 0 ? "No moves needed" : res, symbol);
	}
	return 0;
}

