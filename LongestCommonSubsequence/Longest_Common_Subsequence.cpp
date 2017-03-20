#include<iostream>
using namespace std;

class LCS {
	private:
		void CLCS(int i, int j);
		int **c,**s,m,n; // c[i][j]保存序列Xi和Yj的最长公共子序列的长度
			// 二维数组s用来追踪最长公共子序列
		char *a,*b; // 存储两个序列

	public:
		LCS() {  // 创建二维数组c和s和一维数组a和b,并初始化
			Init();
			LCSLength();
			CLCS();
		}
		int LCSLength(); // 求最优解值--最长公共子序列长度
		void CLCS(); // 构造最优解--最长公共子序列
		void Init();
};

int main() {
	LCS A;
	return 0;
}

int LCS::LCSLength() {
	for(int i=0;i<=m;i++) { c[i][0]=0; }
	for(int i=0;i<=n;i++) { c[0][i]=0; }
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=n;j++) {
			if(a[i]==b[j]) {
				c[i][j]=c[i-1][j-1]+1; // 由c[i-1][j-1]计算c[i][j]
				s[i][j]=1;
			}
			else if(c[i-1][j]>=c[i][j-1]) {
				c[i][j]=c[i-1][j]; // 由c[i-1][j]得到c[i][j]
				s[i][j]=2;
			}
			else {
				c[i][j]=c[i][j-1]; // 由c[i][j-1]得到c[i][j]
				s[i][j]=3;
			}
		}
	}
	return c[m][n]; // 返回最优解值
	// 在二维数组s中,遇到1就向对角线方向(西北方向)走
	//		遇到2就向上走(北)
	//		遇到3就向左走(西)
	// 一直走到0停,路径中是按对角线方向走的那些格便组成最长公共子序列
}

void LCS::CLCS(int i, int j) {
	if(i==0||j==0) return;
	if(s[i][j]==1) {
		CLCS(i-1,j-1); // 只对对角线方向的元素进行输出,得到最长公共子序列
		cout<<a[i];
	}
	else if(s[i][j]==2) 
		CLCS(i-1,j);
	else
		CLCS(i,j-1);
}

void LCS::Init() {
	cout<<"请输入两个序列的长度:(7 6)"<<endl;
	cin>>m; cin>>n;
	cout<<"请输入两个序列:"<<endl;
	cout<<"Example: a b c b d a b / b d c a b a"<<endl;
	a=new char[m+1];
	b=new char[n+1];
	a[0]='0'; b[0]='0';
	for(int i=1;i<=m;i++) {
		cin>>a[i];
	}
	for(int i=1;i<=n;i++) {
		cin>>b[i];
	}
	c=new int*[m+1];
	s=new int*[m+1];
	for(int i=0;i<=m;i++) {
		c[i]=new int[n+1];
		s[i]=new int[n+1];
	}
}

void LCS::CLCS() {
	cout<<"最长公共子序列长度为: "<<LCS::LCSLength()<<endl;
	cout<<"最长公共子序列为: ";
	CLCS(m,n);
	cout<<endl;
}
