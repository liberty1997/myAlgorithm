#include<iostream>
#include<iomanip>
#define MAX_VERTEX_NUM 20
#define INF 999
using namespace std;
//邻接矩阵的定义
typedef struct ArcCell {
	int weight; // 邻接矩阵的元素即为图的边的权值
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	int vexs[MAX_VERTEX_NUM]; // 存放顶点的数组
	AdjMatrix arcs; // 邻接矩阵
	int vexnum,arcnum; //图的当前顶点数和弧数
}MGraph;

class MatrixGraph{
	private:
		int Choose(int *d, bool *s); // 在一维数组d中求最小值
		int N; //图中顶点数
		int **a; //动态生成二维数组a，存储图的邻接矩阵

	public:
		MatrixGraph() {
			CreatAdjMatrix();
		}
		void CreatAdjMatrix();
		void Dijkstra(int s); // s是源点
};

int main() {
	MatrixGraph A;
	//A.CreatAdjMatrix();
	A.Dijkstra(0);
	return 0;
}

void MatrixGraph::CreatAdjMatrix() {
	MGraph G;
	int x,c=0,b=0;
	int A[6][6]={0,50,10,0,70,0,0,0,15,0,10,0,20,0,0,15,0,0,0,20,0,0,35,0,0,0,0,30,0,0,0,0,0,3,0,0};
	cout<<"输入图的顶点数和边数:"<<endl;
	cin>>G.vexnum; cin>>G.arcnum;
	N=G.vexnum;
	cout<<"输入顶点:"<<endl;
	for(int i=0;i<G.vexnum;i++) {
		cin>>G.vexs[i];
	}
	cout<<"图的顶点数和边数分别为: "<<G.vexnum<<" "<<G.arcnum<<endl;
	for(int i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			G.arcs[i][j].weight=INF;
		}
	}
	cout<<"初始化矩阵:"<<endl;
	for(int i3=0;i3<G.vexnum;i3++) {
		for(int j3=0;j3<G.vexnum;j3++) {
			cout<<setw(3)<<G.arcs[i3][j3].weight<<" ";
			c++;
			if(c%G.vexnum==0) cout<<endl;
		}
	}
	cout<<"输入邻接矩阵,有路径请输权值,否则输0:"<<endl;
/*	for(int i1=0;i1<G.vexnum;i1++) {
		for(int j1=0;j1<G.vexnum;j1++) {
			cin>>x;
			if(x!=0) G.arcs[i1][j1].weight=x;
		}
	} */
	cout<<"输入太麻烦,所以内置了矩阵"<<endl;
	for(int i4=0;i4<G.vexnum;i4++) {
		for(int j4=0;j4<G.vexnum;j4++) {
			if(A[i4][j4]!=0) {
				G.arcs[i4][j4].weight=A[i4][j4];
			}
		}
	}

	cout<<"目前邻接矩阵为:"<<endl;
	for(int i2=0;i2<G.vexnum;i2++) {
		for(int j2=0;j2<G.vexnum;j2++) {
			cout<<setw(3)<<G.arcs[i2][j2].weight<<" ";
			b++;
			if(b%G.vexnum==0) cout<<endl;
		}
		cout<<endl;
	}
	cout<<"Congratulations!邻接矩阵建立成功!"<<endl;
	cout<<"将生成的邻接矩阵存储在a数组里"<<endl;
	a=new int*[G.vexnum];
	for(int i=0;i<G.vexnum;i++) {
		a[i]=new int[G.vexnum];
	}
	for(int i5=0;i5<G.vexnum;i5++) {
		for(int j5=0;j5<G.vexnum;j5++) {
			a[i5][j5]=G.arcs[i5][j5].weight;
		}
	}
	cout<<"将图的顶点数存储在N中: N=";
	cout<<" "<<N<<endl;
}

int MatrixGraph::Choose(int *d, bool *s) {
	int i,minpos,min;
	min=INF;minpos=-1;
	for(i=0;i<N;i++) {
		if(d[i]<min && !s[i]) {
			min=d[i];minpos=i;
		}
	}
	return minpos;
}

void MatrixGraph::Dijkstra(int s) {
	int k,i,j;
	int *d;
	int *path;
	cout<<"请输入源点(0~5):"<<endl;
	cin>>s;
	if(s<0||s>N-1) cout<<"ERROR!"<<endl;
	bool *inS=new bool[N];
	d=new int[N];
	path=new int[N];
	for(i=0;i<N;i++) {
		inS[i]=false;
		d[i]=a[s][i];
		if(i!=s && d[i]<INF) path[i]=s;
		else path[i]=-1;
	}
	//将源点加入S集,并设当前最短路径为0,因为此时刚放入源点,
	//d[s]此时表示的是源点到自身的距离,是0
	inS[s]=1;d[s]=0;
	// 循环选出最短路径
	for(i=1;i<N-1;i++) {
		k=Choose(d,inS);
		inS[k]=true;
		for(j=0;j<N;j++) {
			if(!inS[j]&&d[k]+a[k][j]<d[j]) {
				d[j]=d[k]+a[k][j];
				path[j]=k;
			}
		}
	}
	cout<<"vexs   | 路径长度 | 前驱"<<endl;
	for(int m=0;m<N;m++) {
		if(m!=s) cout<<m<<"      |  ";
		if(m!=s) cout<<setw(4)<<d[m]<<"    | ";
		if(m!=s) cout<<setw(2)<<path[m]<<endl;
	}
	// vexs 1  2  3  4  5
	// d	0 45 10 25 55
	//path -1  3  0  2  1
}
