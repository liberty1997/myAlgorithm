#include<iostream>
using namespace std;

template<class T>
class MGraph {
	public:
		MGraph();
		void Hamiltonian(int *x);
		void Init();

	private:
		int *x,n,e; // 一维数组x存放解向量
		int **a; // 存储邻接矩阵
		void Hamiltonian(int k, int *x);
		void NextValue(int k, int *x);
};

int main() {
	MGraph<int> A;
	return 0;
}

template<class T>
MGraph<T>::MGraph() {
	Init();
	cout<<"------Start------"<<endl;
	Hamiltonian(x);
}

template<class T>
void MGraph<T>::Init() {
	int p1,p2;
	cout<<"建立无向图的邻接矩阵:"<<endl;
	cout<<"输入结点数和边数:(8 11)"<<endl;
	cin>>n; cin>>e;
	x=new int[n];
	a=new int*[n];
//	x[0]=0;
	for(int i=0;i<n;i++) a[i]=new int[n];
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			a[i][j]=0;
		}
	}
	cout<<"输入无向图的边:"<<endl;
	cout<<"Example: 0 1, 0 2, 0 6, 1 2, 1 7, 2 3, 2 5,"<<endl;
	cout<<"		3 4, 4 5, 5 6, 6 7"<<endl;
	for(int i=0;i<e;i++) {
		cin>>p1; cin>>p2;
		a[p1][p2]=1;
		a[p2][p1]=1;
	}
}

template<class T>
void MGraph<T>::NextValue(int k, int *x) {
	do {
		int j;
		x[k]=(x[k]+1)%n;	// 下一个结点编号
		if(!x[k]) return;
		if(a[x[k-1]][x[k]]) { // (x[k-1],x[k])是否是图中一条边
			for(j=0;j<k;j++) { // 检查与前k个结点是否相同
				if(x[j]==x[k]) break; // 结点x[k]与前k个结点有重复
			}
			if(j==k) {  // x[k]是当前可取的结点编号
				if((k<n-1)||((k==n-1)&&a[x[n-1]][x[0]]))
					return;
			}
		}
	}while(1);
}

template<class T>
void MGraph<T>::Hamiltonian(int k, int *x) {
	do {
		NextValue(k,x); // 产生x[k]的下一个值
		if(!x[k]) return ; // x[k]=0表示x[k]已经没有可取值
		if(k==n-1) {
			for(int i=0;i<n;i++) {
				cout<<x[i]<<' '; // 输出一个哈密顿环
			}
			cout<<"0"<<endl;
		}
		else {
			Hamiltonian(k+1,x); // 深度优先进入下一层
		}
	}while(1);
}

template<class T>
void MGraph<T>::Hamiltonian(int *x) {
	Hamiltonian(1,x); // x[0]=0 为约定的起始结点
}
