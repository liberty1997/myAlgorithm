// 递归的开始 实现了深度优先遍历
// 递归的结束 实现了回溯
#include<iostream>
using namespace std;

class Queen {
	public:
		void NQueens(int n, int *x);
		Queen() {
			Init();
			NQueens(N,x);
			cout<<"共有"<<sum<<"组解."<<endl;
		}

	private:
		int *x;
		int N;
		int sum=0; // 记录解的个数
		bool Place(int k, int i, int *x);
		void NQueens(int k, int n, int *x);
		void Init();
};

int main() {
	Queen Q;
	return 0;
}

bool Queen::Place(int k, int i, int *x) {
	// 判断两个皇后是否处于同一列和处于同一斜线上
	for(int j=0;j<k;j++) {
		if((x[j]==i)||(abs(x[j]-i)==abs(j-k))) {
			// 因为斜线是45度,所以两个点若在同一斜线上,
			// 那它俩的横向和纵向之间的距离肯定相等
			return false;
		}
	}
	return true;
}

void Queen::NQueens(int k, int n, int *x) {
	// k控制行,i控制列
	for(int i=0;i<n;i++) {
		if(Place(k,i,x)) {
			x[k]=i;
			if(k==n-1) {
				for(i=0;i<n;i++)
					cout<<x[i]<<" ";
				cout<<endl;
				sum++;
			}
			else {
				NQueens(k+1,n,x);
			}
		}
	}
}

void Queen::NQueens(int n, int *x) {
	NQueens(0,n,x);
}

void Queen::Init() {
	cout<<"请输入皇后的个数:"<<endl;
	cin>>N;
	x=new int[N];
	for(int i=0;i<N;i++) {
		x[i]=-1;
	}
}
