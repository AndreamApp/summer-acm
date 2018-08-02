// http://icpcsummer.openjudge.cn/2018hw1/01/
// 注意使用double类型
// 输入输出对应%lf 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 50005;

int L, N, M;
int a[MAX];

// m是常参数，表示最多可移走的石头数
// judge表示在最短步长d的限制下，能否过河
// 则judge函数是关于d的单调递减函数，若a < b，则judge(a) >= judge(b)，可用二分查找分界点 
bool judge(int d, int m){
	long long sum = 0;
	for(int i = 1; i <= N+1 && m >= 0; i++){
		sum += a[i] - a[i-1];
		if(sum < d){
			m--;
		}
		else{
			sum = 0;
		}
	}
	return m >= 0;
}

int search(int a, int b){
	while(b > a + 1){
		int m = (a + b) / 2;
		if(judge(m, M)){
			a = m;
		}
		else{
			b = m;
		}
	}
	// Q: 循环结束后，b-a的取值范围是多少？ 
	if(judge(b, M)) return b; // Q: 如果不加这个条件，在什么情况下会出错？ 
	return a;
}

int main(){
	scanf("%d%d%d", &L, &N, &M);
	for(int i = 1; i <= N; i++){
		scanf("%d", &a[i]);
	}
	a[N+1] = L;
	
	printf("%d", search(0, L));
	
	return 0;
}
