#include <bits/stdc++.h>

using namespace std;

const int inf = 1 << 30;

char chess[5][5];
int best_i = inf, best_j = inf;

int alphaSearch(int depth, int beta);
int betaSearch(int depth, int alpha);

// 根据棋盘判断游戏结果 
int evaluate() {
	for(int i = 0; i < 4; i++){
		if(chess[i][0] == 'x' && chess[i][1] == 'x' && chess[i][2] == 'x' && chess[i][3] == 'x') 
			return 1;
		if(chess[i][0] == 'o' && chess[i][1] == 'o' && chess[i][2] == 'o' && chess[i][3] == 'o') 
			return -1;
		if(chess[0][i] == 'x' && chess[1][i] == 'x' && chess[2][i] == 'x' && chess[3][i] == 'x') 
			return 1;
		if(chess[0][i] == 'o' && chess[1][i] == 'o' && chess[2][i] == 'o' && chess[3][i] == 'o') 
			return -1;
		if(chess[0][0] == 'x' && chess[1][1] == 'x' && chess[2][2] == 'x' && chess[3][3] == 'x') 
			return 1;
		if(chess[0][0] == 'o' && chess[1][1] == 'o' && chess[2][2] == 'o' && chess[3][3] == 'o') 
			return -1;
		if(chess[3][0] == 'x' && chess[2][1] == 'x' && chess[1][2] == 'x' && chess[0][3] == 'x') 
			return 1;
		if(chess[3][0] == 'o' && chess[2][1] == 'o' && chess[1][2] == 'o' && chess[0][3] == 'o') 
			return -1;
	}
	return 0;
}

int alphaSearch(int depth, int beta){
	// o 刚走了一步，现在o胜利了 
	if(evaluate() == -1) return -1;
	// 棋盘已经下满还没分出胜负 
	if(depth <= 0) return 0;
	int best = -inf;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(chess[i][j] == '.'){
				chess[i][j] = 'x';
				best = max(best, betaSearch(depth - 1, best));
				chess[i][j] = '.';
				if(best >= beta)
					return best;
			}
		}
	}
	return best;
}

void print(){
	for(int i = 0; i < 4; i++){
		printf("%s\n", chess[i]);
	}
}

int betaSearch(int depth, int alpha){
	// x 刚走了一步，现在x胜利了 
	if(evaluate() == 1) return 1;
	// 棋盘已经下满还没分出胜负 
	if(depth <= 0) return 0;
	int best = inf;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(chess[i][j] == '.'){
				chess[i][j] = 'o';
				best = min(best, alphaSearch(depth - 1, best));
//				printf("beta best at(%d, %d) = %d\n", i, j, best);
//				print();
				chess[i][j] = '.';
				if(best <= alpha)
					return best;
			}
		}
	}
	return best;
} 

int solve(int depth){
	int best = inf;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(chess[i][j] == '.'){
				// x走(i,j)必胜，即无论o怎么走，x都能获胜 
				chess[i][j] = 'x';
				int ans = betaSearch(depth - 1, -1);
				chess[i][j] = '.';
				if(ans == 1){
					best_i = i;
					best_j = j;
					return 1;
				}
			}
		}
	}
	return 0;
}

int main(){
	char sign[2];
	while(~scanf("%s", sign) && '?' == sign[0]){
		int depth = 0;
		for(int i = 0; i < 4; i++){
			scanf("%s", chess[i]);
			for(int j = 0; j < 4; j++){
				if(chess[i][j] == '.')
					depth++; 
			}
		}
		
		if(depth >= 12){
			printf("#####\n");
		}
		else if(solve(depth)){
			printf("(%d,%d)\n", best_i, best_j);
		}
		else{
			printf("#####\n");
		}
	}
	return 0;
}

