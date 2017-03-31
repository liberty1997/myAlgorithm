#include<iostream>
#include<algorithm>
using namespace std;

class Subset_and_number {
	public:
		void SumOfSub(int *x, int n, float m, float *w);
		Subset_and_number();

	private:
		void SumOfSub(float s,int k, float r, int *x, float m, float *w);
		float *w,m;
		int *x,n;
};

int main() {
	Subset_and_number S;
	return 0;
}

Subset_and_number::Subset_and_number() {
	SumOfSub(x,n,m,w);
}

void Subset_and_number::SumOfSub(float s, int k, float r, int *x, float m, float *w) {
	x[k]=1;
	if(s+w[k]==m) { // 得到一个可行解
		for(int j=0;j<=k;j++) cout<<x[j]<<" ";
		cout<<endl;
	}
	else if(s+w[k]+w[k+1]<=m)
		SumOfSub(s+w[k],k+1,r-w[k],x,m,w); // 搜索左子树
	if((s+r-w[k]>=m)&&(s+w[k+1]<=m)) {
		x[k]=0;
		SumOfSub(s,k+1,r-w[k],x,m,w); // 搜索右子树
	}
}

void Subset_and_number::SumOfSub(int *x, int n, float m, float *w) {
	float r=0;
	cout<<"请输入n和m:(6 30)"<<endl;
	cin>>n; cin>>m;
	w=new float[n];
	x=new int[n];
	cout<<"请输入集合:(5 10 15 12 13 18)"<<endl;
	for(int i=0;i<n;i++) cin>>w[i];
	for(int i=0;i<n-1;i++) {
		if(w[i]>w[i+1]) {
			cout<<"对集合元素进行升序排序."<<endl;
			sort(w,w+n);
			break;
		}
	}
	for(int i=0;i<n;i++) r=r+w[i];
	if(r>=m && w[0]<=m) SumOfSub(0,0,r,x,m,w);
}
