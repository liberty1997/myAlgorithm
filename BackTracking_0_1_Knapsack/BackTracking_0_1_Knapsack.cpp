// modified on 04/06/2017
// 运用了vector和sort
// 将冒泡排序改成了sort
// 使用了sort的三种方法,其中方法二不能用---当结构体用到模板参数时
// 使用了auto且传引用 (auto &a:s)
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>

template<class T>
struct Pack {
	T w1,p1;
	double pw;
};

// 利用sort依据结构体里的某个元素进行排序时
// 有两种对sort重写的方法
// 1.重载operator<
// 2.自定义cmp函数

// sort方法一
template<class T>
bool operator<(const Pack<T> &a1, const Pack<T> &a2) { return a1.pw>a2.pw; }

// sort方法二
// 用cmp时,sort函数是sort(pack.begin(),pack.end(),cmp);
// cmp这个,一加上模板参数就不行了
/*template<class T>
bool cmp(struct Pack<T> a, struct Pack<T> b) {
	return a.pw>b.pw; // 大于还是小于取决于需求
}  */

using namespace std;

template<class T>
class Knapsack {
	public:
		Knapsack();
		void Init();
		T BKnapsack(int *x);
		void swap(int &a, int &b);

	protected:
		void BKnapsack(int k, T cp, T cw, T &fp, int *x, int *y);
		T Bound(int k, T cp, T cw);
		T m, *w, *p;
		int n,*x;
};

int main() {
	Knapsack<int> A;
	return 0;
}

template<class T>
Knapsack<T>::Knapsack() {
	Init();
	BKnapsack(x);
}

template<class T>
void Knapsack<T>::Init() {
	cout<<"输入物品个数:(8)"<<endl;
	cin>>n;
	cout<<"输入背包重量:(110)"<<endl;
	cin>>m;
	T q,r;
	double e;
	vector<struct Pack<T> > pack(n);
	cout<<"输入物品的w和p:"<<endl;
	cout<<"Example:1 11, 11 21, 21 31, 23 33, 33 43, 43 53,"<<endl;
	cout<<"        45 55, 55 65"<<endl;
	for(auto &i:pack) {
		cin>>i.w1;
		cin>>i.p1;
		i.pw=(i.p1/i.w1);
	}
	// 按单位重量排序
	// 以下注释是sort方法三
/*	struct {
		bool operator() (struct Pack<T> a1, struct Pack<T> a2) {
			return a1.pw>a2.pw;
		}
	}cmp;
	sort(pack.begin(), pack.end(),cmp); */
	sort(pack.begin(), pack.end());
	w=new T[n];
	p=new T[n];
	x=new int[n];
	for(int i=0;i<n;i++) {
		w[i]=pack[i].w1;
		p[i]=pack[i].p1;
	}

}

template<class T>
T Knapsack<T>::Bound(int k, T cp, T cw) {
	// cp是当前收益,cw是当前背包重量,k是当前待考察的物品编号
	T b=cp,c=cw;
	for(int i=k+1;i<n;i++) {
		c+=w[i];
		if(c<m) b+=p[i];
		else return (b+(1-(c-m)/w[i])*p[i]);
	}
	return b;
}

template<class T>
void Knapsack<T>::BKnapsack(int k, T cp, T cw, T &fp, int *x, int *y) {
	// fp是当前最大收益,初始时fp=0
	// 考察左孩子结点
	int j;
	T bp;
	if(cw+w[k]<=m) { // 左子树需要重新计算约束函数,无须计算子树的上界函数
		y[k]=1;
		if(k<n-1) BKnapsack(k+1,cp+p[k],cw+w[k],fp,x,y);
		if(cp+p[k]>fp && k==n-1) {
			fp=cp+p[k]; // 找到一个收益更高的可行解
			for(j=0;j<=k;j++) x[j]=y[j]; // x[k]中保存对应于fp的可行解
		}
	}
	// 考察右孩子结点
	if(Bound(k,cp,cw)>=fp) { // 对右孩子需要重新计算上界函数
		y[k]=0;
		if(k<n-1) BKnapsack(k+1,cp,cw,fp,x,y);
		if(cp>fp&&k==n-1) { // 找到一个收益更高的可行解
			fp=cp;
			for(j=0;j<k;j++) x[j]=y[j];
		}
	}
}

template<class T>
T Knapsack<T>::BKnapsack(int *x) {
	// 一维数组x中返回最优解向量,函数返回最优解值
	int y[n]={0};
	T fp;
	BKnapsack(0,0,0,fp,x,y);
	cout<<"最优解为:"<<endl;
	for(int i=0;i<n;i++) {
		cout<<x[i]<<" ";
	}
	cout<<endl;
	cout<<"最优解值为:"<<endl;
	cout<<" "<<fp<<endl;
	return fp;
}

template<class T>
void Knapsack<T>::swap(int &a, int &b) {
	int temp;
	temp=a;
	a=b;
	b=temp;
}
