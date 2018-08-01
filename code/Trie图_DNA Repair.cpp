#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

const int BRANCH = 4;
const int inf = 0x3f3f3f3f;

struct Node{
	Node * childs[BRANCH];
	Node * prev; // 前缀指针 
	bool bad; // 危险结点 
};

Node tree[1005]; // N * L <= 50 * 20 = 1000
int nodeCount; // 初始化为2，0号结点和1号结点单独初始化 

/*
 状态：dp[i][j]表示母串长度为i的前缀，遍历到达节点j（安全节点），需要修改的最少次数
       0<=i<=len(str), 1<=j<nodeCount，min(dp[len][j])就是答案 
 条件：dp[0][1] = 0; 表示母串长度为0的前缀只需修改0次就能到达1号结点（根节点）
       其他的dp[i][j] = inf; 
 转移：dp[i+1][son(j)] = min(dp[i+1][son(j)], dp[i][j] + Char(j, son(j)) != str[i]) 
       Char(j, son(j)) != str[i] 表示母串的第i+1个字符是否和j到达son(j)所需的字符相同，即母串是否需要再修改一个字符才能到达son(j) 
*/
int dp[1005][1005];

inline int hash(char c){
	return 'A' == c ? 0
		: 'G' == c ? 1
		: 'C' == c ? 2
		: 3;
//	return c - 'a';
}

Node * newNode(){
	Node * node = tree + nodeCount;
	nodeCount++;
	return node;
}

// 将模式串插入Trie树中 
void insertTrieTree(char * dna){
	Node * root = &tree[0];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->childs[c] == NULL){
			root->childs[c] = tree + nodeCount;
			nodeCount++;
		}
		root = root->childs[c];
	}
	root->bad = true;
}

// 向Trie树中添加前缀指针，构造Trie图：即为所有结点设置合适的prev和bad 
void buildTrieMap(){
	queue<Node*> q;
	Node * root = &tree[0];
	for(int i = 0; i < BRANCH; i++){
		if(root->childs[i]){
			root->childs[i]->prev = root;
			q.push(root->childs[i]);
		}
		else{
			root->childs[i] = root;
		}
	}
	root->prev = NULL;
	
	while(q.size()){
		Node * p = q.front(); q.pop();
		for(int i = 0; i < BRANCH; i++){
			if(p->childs[i]){
				p->childs[i]->prev = p->prev->childs[i];
				p->childs[i]->bad |= p->prev->childs[i]->bad;
				q.push(p->childs[i]);
			}
			else{
				p->childs[i] = p->prev->childs[i];
			}
		}
	}
}

int searchPattern(char * dna){
	memset(dp, inf, sizeof dp);
	dp[0][0] = 0;
	
	int now = 0, pre = 1;
	for(int i = 0; dna[i]; i++){
		now ^= 1, pre ^= 1;
		memset(dp[now], inf, sizeof dp[now]); // 滚动数组必备 
		int c = hash(dna[i]);
		for(int j = 0; j < nodeCount; j++){
			if(dp[pre][j] == inf) continue;
			Node * p = &tree[j];
			for(int k = 0; k < BRANCH; k++){
				if(!p->childs[k]->bad){
					int sonj = p->childs[k] - tree;
					dp[now][sonj] = min(dp[now][sonj], dp[pre][j] + (c != k));
				}
			}
		}
	}
	
	int len = strlen(dna);
	int ans = inf;
	for(int i = 0; i < nodeCount; i++){
		ans = min(ans, dp[now][i]);
	}
	if(ans == inf) ans = -1;
	return ans;
}

int main(){
	int n, m;
	char dna[1005];
	int t = 0;
	while(~scanf("%d", &n) && n){
		memset(tree, 0, sizeof tree);
		nodeCount = 1;
		for(int i = 0; i < n; i++){
			scanf("%s", dna);
			insertTrieTree(dna);
		}
		buildTrieMap();
		scanf("%s", dna);
		printf("Case %d: %d\n", ++t, searchPattern(dna));
	}
	return 0;
}

