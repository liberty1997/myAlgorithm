#include<iostream>
#include<iomanip>
#define INF 999
#define MAX_VERTEX_NUM 20
using namespace std;

typedef struct ArcCell {
	int weight;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	int vexnum,arcnum;
	int vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
}AMGraph;

class MGraph {
	private:
		void Floyd();
	public:
		MGraph() {
			AMGraph G;
			CreatAdjMatrix(G);
			Floyd();
		}
		int **a;
		int N;
		void CreatAdjMatrix(AMGraph &G);
};

int main()
{
	MGraph A;
	return 0;
}

void MGraph::CreatAdjMatrix(AMGraph &G) {
	int a2,b;
	cout<<"请输入图的顶点数和边数:(4 8)"<<endl;
	cin>>G.vexnum;
	cin>>G.arcnum;
	N=G.vexnum;
	cout<<"请输入顶点:(0 1 2 3)"<<endl;
	for(int i=0;i<G.vexnum;i++) {
		cin>>G.vexs[i];
	}
	for(int i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			if(i==j) 
				G.arcs[i][j].weight=0;
			else
				G.arcs[i][j].weight=INF;
		}
	}
	cout<<"输入边的尾和头和权值:"<<endl;
	cout<<"Example: 0 1 1, 0 3 4, 1 2 9, 1 3 2, 2 0 3, 2 1 5, 2 3 8, 3 2 6"<<endl;
	// 创建邻接矩阵
	for(int i=0;i<G.arcnum;i++) {
		cin>>a2;
		cin>>b;
		cin>>G.arcs[a2][b].weight;
	}
	// 用动态二维数组a存储邻接矩阵
	a=new int*[G.vexnum];
	for(int i=0;i<G.vexnum;i++) {
		a[i]=new int[G.vexnum];
	}
	for(int i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			a[i][j]=G.arcs[i][j].weight;
		}
	}
}

void MGraph::Floyd() {
	int i,j,k;
	int **d,**path;
	int a1=0,b1=0; // 输出二维数组d和path的计数器
	d=new int*[N];
	path=new int*[N];
	for(int m=0;m<N;m++) {
		d[m]=new int[N];
		path[m]=new int[N];
		for(int n=0;n<N;n++) {
			d[m][n]=a[m][n];
			if(m!=n && d[m][n]<INF)
				path[m][n]=m;
			else
				path[m][n]=-1;
		}
	}
	// 对每个结点进行判断,是不是有另外两个结点
	//会因为绕一下自己而使这两个结点间的距离增加
	for(k=0;k<N;k++) {
		for(i=0;i<N;i++) {
			for(j=0;j<N;j++) {
				if(d[i][k]+d[k][j]<d[i][j]) {
					d[i][j]=d[i][k]+d[k][j];
					path[i][j]=path[k][j];
				}
			}
		}
	}
	cout<<"d[i][j]记录从i到j的最短路径长度:"<<endl;
	for(int i1=0;i1<N;i1++) {
		for(int j1=0;j1<N;j1++) {
			cout<<d[i1][j1]<<" ";
			a1++;
			if(a1%N==0) cout<<endl;
		}
	}
	cout<<"path[i][j]记录从i到j的最短路径上j的前一个结点:"<<endl;
	for(int i1=0;i1<N;i1++) {
		for(int j1=0;j1<N;j1++) {
			cout<<path[i1][j1]<<" ";
			b1++;
			if(b1%N==0) cout<<endl;
		}
	}

}
