// http://icpcsummer.openjudge.cn/2018hw1/03/
// 将一些小矩形分为左右两部分，使得左边面积>=右边
// 同时左右两边面积之差最小，大矩形左边面积尽可能大
/*
很容易想到使用二分来做：
解：满足上述条件的k, k为整数 
解空间：[0, R] 中的整数
判别函数：f(k) = 左边小矩形面积 - 右边小矩形面积，单调递增
解法：二分法求k0使得f(k0) >= 0，然后找k1的下界使得f(k1) == f(k0) 

注意：
1. 搜索的边界( [0,R] or [0,R+1] )
2. 搜索的条件( upperbound or lowerbound ) 
*/ 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 10005;

struct rect{
	long long left, right, width, height;
};

int R, N;
rect r[MAX];

// judge(k) 表示k左边的矩形 - k右边的矩形面积
// 易证judge(k)关于k单调递增 
long long judge(int k){
	long long lsum = 0, rsum = 0;
	for(int i = 0; i < N; i++){
		if(r[i].right <= k){
			lsum += r[i].width * r[i].height;
		}
		else if(r[i].left >= k){
			rsum += r[i].width * r[i].height;
		}
		else{
			lsum += (k - r[i].left) * r[i].height;
			rsum += (r[i].right - k) * r[i].height;
		}
	}
	return lsum - rsum;
}

int search(int a, int b){
	// find the minimum positive fk
	// b是我们想要的结果，b遍取(0,R] 
	long long fk;
	while(b - a > 1){
		int m = (a + b) / 2;
		fk = judge(m);
		if(fk > 0){
			b = m;
		}
		else if(fk < 0){
			a = m;
		}
		else{
			a = b = m;
			break;
		}
	}
	// find the upper bound of fk
	double fk0 = judge(b) + 0.5;
	a = 0, b = R+1; // 注意a是我们需要的结果, 为了使a能遍取[0,R]，设置b=R+1 
	while(b - a > 1){
		int m = (a + b) / 2;
		fk = judge(m);
		if(fk > fk0){
			b = m;
		}
		else if(fk < fk0){
			a = m;
		}
	}
	return a;
}

int main(){
	scanf("%d%d", &R, &N);
	long long t;
	for(int i = 0; i < N; i++){
		scanf("%lld%lld%lld%lld", &r[i].left, &t, &r[i].width, &r[i].height);
		r[i].right = r[i].width + r[i].left;
	}
	
	printf("%d", search(0, R));
	
	return 0;
}
