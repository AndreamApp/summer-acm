#include <bits/stdc++.h>

using namespace std;

const int CHILD = 26;

struct Node{
	Node * childs[CHILD];
	Node * prev; // 前缀指针 
	bool bad; // 危险结点 
};

Node tree[500000]; // 250 * 1000 <= 500000
int nodeCount;

inline int hash(char c){
	return c - 'A';
}

// 将模式串插入Trie树中 
void insertTrieTree(char * dna){
	Node * root = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->childs[c] == NULL)
			root->childs[c] =  tree + nodeCount++;
		root = root->childs[c];
	}
	root->bad = true;
}

// 向Trie树中添加前缀指针，构造Trie图：即为所有结点设置合适的prev和bad 
void buildTrieMap(){
	for(int i = 0; i < CHILD; i++){
		tree[0].childs[i] = &tree[1];
	}
	tree[0].prev = NULL;
	tree[1].prev = &tree[0];
	// 使用栈模拟深度优先搜索 
	deque<Node*> q;
	q.push_back(&tree[1]);
	while(q.size()){
		Node * root = q.back(); q.pop_back();
		// 对于每一个子节点 
		for(int i = 0; i < CHILD; i++){
			Node * child = root->childs[i];
			if(child){
				// 沿着父节点的前缀结点 
				Node * prev = root->prev;
				while(prev){
					if(prev->childs[i]){ // 匹配相同后缀 
						child->prev = prev->childs[i];
						if(child->prev->bad) child->bad = true; // 危险结点 
						break;
					}
					prev = prev->prev;
				}
				// 递归构造前缀指针 
				q.push_back(child);
			}
		}
	}
}

/*
从ROOT出发，按照当前串的下一
个字符ch来进行在树上的移动。若当前点P不存在通过ch
连接的儿子，那么考虑P的前缀指针指向的节点Q，如果还
无法找到通过ch连接的儿子节点，再考虑Q的前缀指针…
直到找到通过ch连接的儿子，再继续遍历。

如果遍历过程中经过了某个终止节点，则说明S包含该终
止节点代表的模式串.

如果遍历过程中经过了某个非终止节点的危险节点，
则可以断定S包含某个模式串。要找出是哪个，沿着危险
节点的前缀指针链走，碰到终止节点即可。
*/
int searchPattern(char * dna){
	int res = 0;
	Node * root = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->bad){
			res++;
		}
		if(root->childs[c]){
			root = root->childs[c];
			if(dna[i+1] == 0 && root->bad){
				res++;
			}
		}
		else{
			Node * prev = root->prev;
			while(prev){
				if(prev->childs[c]){ // 找到某个后缀匹配，可以继续搜索 
					root = prev->childs[c];
					break;
				}
				prev = prev->prev;
			}
			// 通过前缀指针找到0号结点了：没有匹配的模式串 
			if(prev == NULL){
				break;
			}
		}
	}
	return res;
}

int main(){
	int t, n;
	char virus[1005]; 
	char program[1005]; 
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%s", virus);
			insertTrieTree(virus);
		} 
		buildTrieMap();
		scanf("%s", program);
		printf("%d", searchPattern(program));
	}
	return 0;
}

