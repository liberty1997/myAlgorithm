// #include<bits/stdc++.h>
#include<iostream>
#define INF 999
using namespace std;

class OBST {
	public:
		void CreatOBST(float *p, float *q, float **c, int **r, float **w, int n);
		OBST() {
			CreatOBST(p,q,c,r,w,n);
		}
		float *p,*q,**c,**w;
		int **r,n;

	private:
		int Find(int i, int j, int **r, float **c);
};

int main() {
	OBST A;
	return 0;
}

int OBST::Find(int i, int j, int **r, float **c) {
	float min=INF;
	int k;
	for(int m=i+1;m<=j;m++) {
		if((c[i][m-1]+c[m][j])<min) {
			min=c[i][m-1]+c[m][j];
			k=m;
		}
	}
	return k;
}

void OBST::CreatOBST(float *p, float *q, float **c, int **r, float **w, int n) {
	cout<<"输入结点数:(4)"<<endl;
	cin>>n;
	cout<<"输入查找成功的概率p[i]和不成功的概率q[i]:"<<endl;
	cout<<"Example: 0 3 3 1 1, 2 3 1 1 1 "<<endl;
	p=new float[n+1];
	q=new float[n+1];
	c=new float*[n+1];
	w=new float*[n+1];
	r=new int*[n+1];
	for(int i=0;i<n+1;i++) {
		c[i]=new float[n+1];
		w[i]=new float[n+1];
		r[i]=new int[n+1];
	}
	for(int i=0;i<n+1;i++) {
		cin>>p[i];
	}
	for(int i=0;i<n+1;i++) {
		cin>>q[i];
	}
	for(int i=0;i<=n-1;i++) {
		w[i][i]=q[i];
		c[i][i]=0.0;
		r[i][i]=0;
		w[i][i+1]=q[i]+q[i+1]+p[i+1];
		c[i][i+1]=q[i]+q[i+1]+p[i+1];
		r[i][i+1]=i+1;
	}
	w[n][n]=q[n];
	c[n][n]=0.0;
	r[n][n]=0;
	for(int m=2;m<=n;m++) {
		for(int i=0;i<=n-m;i++) {
			int j=i+m;
			w[i][j]=w[i][j-1]+p[j]+q[j];
			int k=Find(i,j,r,c);
			c[i][j]=w[i][j]+c[i][k-1]+c[k][j];
			r[i][j]=k;
		}
	}
	for(int i=0;i<n+1;i++) {
		for(int k=0;k<i;k++) {
			cout<<"  ";
		}
		for(int j=i;j<n+1;j++) {
			cout<<r[i][j]<<" ";
		}
		cout<<endl;
	}
}
