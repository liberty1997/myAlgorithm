#include<iostream>
using namespace std;

class MatrixChain {
	private:
		void Traceback(int i, int j); // 构造最优解的私有递归函数
		int LookupChain(int i, int j); // 备忘录方法私有递归
		int *p,**m,**s,N; // n个矩阵连乘的n+1个维数保存在一维数组p中
		                  // 二维数组m用来保存矩阵连乘时所需的最少计算量
				  // 二维数组s用来保存矩阵连乘时的最优计算次序的断开位置

	public:
		MatrixChain() {
			// 初始化二维数组m和s,将它俩的上三角置0,
			//一维数组p手动输入--连乘矩阵的维数
			Init();
		}
		int LookupChain(); // 备忘录方法求最优解值
		void Traceback(); // 构造最优解的公有函数
		void Init();
};

int main() {
	MatrixChain A;
	A.LookupChain();
	A.Traceback();
	return 0;
}

void MatrixChain::Init() {
	cout<<"请输入连乘的矩阵数:(6)"<<endl;
	cin>>N;
	p=new int[N+1];
	m=new int*[N]; // 给二维数组分配空间,行(hang)
	s=new int*[N];
	cout<<"请输入"<<N<<"个矩阵的"<<N+1<<"个维数:"<<endl;
	cout<<"Example: 30 35 15 5 10 20 25"<<endl;
	for(int i=0;i<N+1;i++) {
		cin>>p[i];
	}
	for(int i=0;i<N;i++) {
		m[i]=new int[N];
		s[i]=new int[N];
	}
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			m[i][j]=0;
			s[i][j]=0;
		}
	}
	
}

int MatrixChain::LookupChain(int i, int j) {
	if(m[i][j]>0) return m[i][j];
	if(i==j) return 0;
	int u=LookupChain(i+1,j)+p[i]*p[i+1]*p[j+1];
	s[i][j]=i;
	for(int k=i+1;k<j;k++) {
		int t=LookupChain(i,k)+LookupChain(k+1,j)+p[i]*p[k+1]*p[j+1];
		if(t<u) {
			u=t;
			s[i][j]=k;
		}
	}
	m[i][j]=u;
	return u;
}

int MatrixChain::LookupChain() {
	return LookupChain(0,N-1);
}

void MatrixChain::Traceback(int i, int j) {
	if(i==j) { // 单个矩阵不用断开
		cout<<'A'<<i;
		return ;
	}
	if(i<s[i][j]) cout<<'(';Traceback(i,s[i][j]); if(i<s[i][j]) cout<<')';
	if(s[i][j]+1<j) cout<<'(';Traceback(s[i][j]+1,j); if(s[i][j]+1<j) cout<<')';
}

void MatrixChain::Traceback() {
	cout<<'(';Traceback(0,N-1);cout<<')';
	cout<<endl;
}
