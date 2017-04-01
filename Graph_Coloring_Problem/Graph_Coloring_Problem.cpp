#include<iostream>
using namespace std;

template<class T>
class MGraph {
	public:
		void mColoring(int m, int *x);
		void Init();
		MGraph();

	private:
		int **a; // 动态二维数组用来存储邻接矩阵
		int *x; // 一维数组x用来保存一个解向量
		int m,n,e;  // m为颜色数,n为图的结点数,edge为边数
		void NextValue(int k, int m, int *x);
		void mColoring(int k, int m, int *x);
};

int main() {
	MGraph<int> A;
	return 0;
}

template<class T>
void MGraph<T>::Init() {
	int p1,p2;
	cout<<"请输入结点数和边数和颜色数:(4 5 3)"<<endl;
	cin>>n; cin>>e; cin>>m;
	x=new int[n];
	a=new int*[n];
	for(int i=0;i<n;i++) {
		a[i]=new int[n];
	}
	// 初始化邻接矩阵a,全为0
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			a[i][j]=0;
		}
	}
	cout<<"输入边:"<<endl;
	cout<<"Example: 0 1, 0 3, 1 2, 2 3, 1 3"<<endl;
	for(int i=0;i<e;i++) {
		cin>>p1; cin>>p2;
		a[p1][p2]=1;
		a[p2][p1]=1;
	}
}

template<class T>
void MGraph<T>::NextValue(int k, int m, int *x) {
	// 本函数在[1,m]中为x[k]确定一个值最小的且不与邻接点冲突的颜色
	// x[k]=0 表示没有可用的颜色,颜色从1开始编号
	do {
		int j;
		x[k]=(x[k]+1)%(m+1); // 尝试下一种颜色
		if(!x[k]) return ; // 没有可用颜色
		for(j=0;j<k;j++) {
			if(a[k][j] && x[k]==x[j]) break; // 若(k,j)是图的边,且相邻结点k和j
							// 颜色相同,则颜色冲突,选下一种颜色
		}
		if(j==k) return ; // 成功选择一种颜色 返回
	}while(1);
}

template<class T>
void MGraph<T>::mColoring(int k, int m, int *x) {
	do {
		NextValue(k,m,x); // 为x[k]分配颜色
		if(!x[k]) break; // x[k]=0表示当前没有适当的颜色
		if(k==n-1) {	// 得到图G的一种m-着色方案
			for(int i=0;i<n;i++) cout<<x[i]<<" ";
			cout<<endl;
		}
		else
			mColoring(k+1,m,x); // 已经对前k个结点分配了颜色,尝试其余结点
	}while(1);
}

template<class T>
void MGraph<T>::mColoring(int m, int *x) {
	mColoring(0,m,x);
}

template<class T>
MGraph<T>::MGraph() {
	Init();
	mColoring(m,x);
}
