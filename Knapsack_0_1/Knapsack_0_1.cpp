// 所有注释掉的cout均为调试所用
// 错误原因见103行
#include<iostream>
using namespace std;

struct XP {
	float X,P;
};

template<class T>
class Knapsack {
	public:
		Knapsack();
		//T DKnap(int *x);

	private:
		T DKnap();
		void TraceBack(int *x);
		int Largest(int low, int high, int i);
		float m, *w;
		XP *p;
		T *pf;
		int n,*b;
};

int main() {
	Knapsack<int> A;
	return 0;
}

template<class T> 
Knapsack<T>::Knapsack() {
	int *x;
	cout<<"请输入物品的个数:(3)"<<endl;
	cin>>n;
	cout<<"请输入背包容量:(6.0)"<<endl;
	cin>>m;
	cout<<"请输入物品的重量:(2.0 3.0 4.0)"<<endl;
	x=new int[n];
	w=new float[n];
	pf=new T[n];
	p=new XP[n+9];
	b=new int[n+1];
	for(int i=0;i<n;i++) {
		cin>>w[i];
	}
	cout<<"请输入物品的利润:(1 2 4)"<<endl;
	for(int i=0;i<n;i++) {
		cin>>pf[i];
	}
	DKnap();
	TraceBack(x);
}

template<class T>
int Knapsack<T>::Largest(int low, int high, int i) {
	int u=low-1;
	for(int j=low;j<=high;j++) {
		float ww=p[j].X+w[i];
		//cout<<"p["<<j<<"].X="<<p[j].X<<endl;
		//cout<<"w["<<i<<"]="<<w[i]<<endl;
		if(ww<=m) {
			u=j;
			//cout<<"Largest u="<<u<<endl;
		}
	}
	return u;
}

template<class T>
T Knapsack<T>::DKnap() {
	float ww,pp;
	int next;
	b[0]=0;
	p[0].X=p[0].P=0.0;
	p[1].X=w[0];
	p[1].P=pf[0];
	//cout<<"p[0].X="<<p[0].X<<endl;
	//cout<<"p[0].P="<<p[0].P<<endl;
	//cout<<"p[1].X="<<p[1].X<<endl;
	//cout<<"p[1].P="<<p[1].P<<endl;
	int low=0;
	int high=1;
	b[1]=next=2;
	//cout<<"b[1]="<<b[1]<<endl;
	for(int i=1;i<=n-1;i++) {
		int k=low;
		int u=Largest(low,high,i);
		//cout<<"u="<<u<<endl;
		for(int j=low;j<=u;j++) {
			ww=p[j].X+w[i];
			pp=p[j].P+pf[i];
			while((k<=high)&&(p[k].X<ww)) {
				p[next].X=p[k].X;
				//cout<<"p["<<next<<"].X="<<p[next].X<<endl;
				p[next++].P=p[k++].P;
				//cout<<"p[next++]="<<p[next+1].P<<endl;
			}
			if(k<=high&&p[k].X==ww)
				if(pp<p[k].P)
					pp=p[k++].P;
			if(pp>p[next-1].P) {
				p[next].X=ww; // 错误原因在此行,之前写成了‘==’
				p[next++].P=pp;
			}
			while(k<=high && p[k].P<=p[next-1].P) k++;
		}
		while(k<=high) {
			p[next].X=p[k].X;
			p[next++].P=p[k++].P;
		}
		low=high+1;
		high=next-1;
		b[i+1]=next;
		/*cout<<"low="<<low<<endl;
		cout<<"next="<<next<<endl;
		cout<<"high="<<high<<endl;
		cout<<"b["<<i+1<<"]="<<b[i+1]<<endl; */
		
	} /*
	for(int i=0;i<n+5;i++) {
		cout<<"X"<<p[i].X<<" ";
		cout<<"P"<<p[i].P<<" ";
	}
	cout<<endl; */
	return p[next-1].P;
}

template<class T>
void Knapsack<T>::TraceBack(int *x) {
	float ww=p[b[n]-1].X;
	//cout<<"b[n]="<<b[3]<<endl;
	//cout<<"p[b[n]-1].X="<<p[b[n]-1].X<<endl;
	//cout<<"TraceBack ww="<<ww<<endl;
	//x=new int[n];
	for(int j=n-1;j>0;j--) {
		x[j]=1;
		/*cout<<"j="<<j<<endl;
		cout<<"b[2]="<<b[2]<<endl;
		cout<<"b[1]="<<b[1]<<endl;
		cout<<"b[0]="<<b[0]<<endl; */
		for(int k=b[j-1];k<b[j];k++) {
			//cout<<"p["<<k<<"].X="<<p[k].X<<" ";
			//cout<<"ww="<<ww<<" ";
			if(ww==p[k].X) x[j]=0;
		}
		if(x[j]) ww=ww-w[j];
	}
	if(ww==0) x[0]=0; else x[0]=1;
	cout<<"解的情况:"<<endl;
	for(int i=0;i<n;i++) {
		cout<<x[i]<<" ";
	}
	cout<<endl;
}
