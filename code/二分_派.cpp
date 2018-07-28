// http://icpcsummer.openjudge.cn/2018hw1/01/
// 注意使用double类型
// 输入输出对应%lf 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 10005;

int N, F;
double a[MAX];

bool judge(double v){
	int cnt = 0;
	for(int i = 0; i < N; i++){
		cnt += int(a[i] / v);
	}
	return cnt >= F+1;
}

double search(double a, double b, double error){
	while(b - a > error){
		double m = (a + b) / 2; // 用float可能溢出导致死循环 
		if(judge(m)){
			a = m;
		}
		else{
			b = m;
		}
	}
	return a;
}

int main(){
	scanf("%d%d", &N, &F);
	double mx = 0;
	for(int i = 0; i < N; i++){
		scanf("%lf", &a[i]);
		a[i] = a[i] * a[i] * 3.1415926535897932384626;
		if(a[i] > mx) mx = a[i];
	}
	
	printf("%.3lf", search(0, mx + 10, 0.0001));
	
	return 0;
}
