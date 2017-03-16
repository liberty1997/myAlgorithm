// 多段图的向前递推算法
// 本段程序对应教材<算法设计与分析>中的多段图那节的图
// 最短路径本有两条 0 2 5 9 11 and 0 1 6 9 11
// 本算法只能求出一条,结果由输入的邻接点的顺序决定
#include<iostream>
#include<cstdlib>
#include<iomanip>
#define INF 999
#define MAX_VERTEX_NUM 30
using namespace std;

// 边结点
typedef struct ArcNode {
	int adjvex; //当前顶点的邻接点的位置信息,如 下标或序号
	int weight; // 弧的权值
	struct ArcNode *nextarc; //邻接点的指针域,指向下一个邻接点;
}ArcNode;

// 头结点
typedef struct VNode {
	int data; //顶点信息,比如顶点名称
	ArcNode *firstarc; // 邻接表头节点的指针域,指向顶点的第一个邻接点
}VNode, AdjList[MAX_VERTEX_NUM];

// 图
typedef struct {
	AdjList vertices;
	int vexnum,arcnum;
}ALGraph;

class AGraph {
	private:
		void FMultiGraph(int k);
		int N; // 存储图的顶点数
		int **a;
	public:
		void CreatAdjList(ALGraph &G);
		AGraph() { 
			//ALGraph G;
			//CreatAdjList(G);
			FMultiGraph(5);
		}
};

int main() {
	AGraph A;
	return 0;
}

// 创建 有向带权图的邻接表,无向图比这个多一点
// 因为无向图两个顶点间是互通的
void AGraph::CreatAdjList(ALGraph &G) {
	ArcNode *p;
	int m,n,w;
	cout<<"请输入顶点数和边数:(12 21)"<<endl;
	cin>>G.vexnum;
	cin>>G.arcnum;
	N=G.vexnum;
	cout<<"请输入顶点:(0~11)"<<endl;
	for(int i=0;i<G.vexnum;i++) {
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	cout<<"输入弧的尾和头及其权值:"<<endl;
	cout<<"Example: 0 1 9, 0 2 7, 0 3 3, 0 4 2, 1 5 4, 1 6 2,"<<endl;
	cout<<"         1 7 1, 2 5 2, 2 6 7, 3 7 11, 4 6 11, 4 7 8,"<<endl;
	cout<<"         5 8 6, 5 9 5, 6 8 4, 6 9 3, 7 9 5, 7 10 6, 8 11 4,"<<endl;
	cout<<"         9 11 2, 10 11 5"<<endl;
	cout<<"请一条边一条边得输入!"<<endl;
	for(int i1=0;i1<G.arcnum;i1++) {
		cout<<"请输入第"<<i1+1<<"条边"<<endl;
		cin>>m;
		cin>>n;
		cin>>w;
		// 生成新的边结点,并将其插在单链表的头部
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=n;
		p->weight=w;
		p->nextarc=G.vertices[m].firstarc;
		G.vertices[m].firstarc=p;
		// 以上完成了将一个邻接点插入表头的操作
	}
	ArcNode *s;
	cout<<"检验邻接矩阵是否正确输入:"<<endl;
	cout<<"顶点 |  adjvex |权值"<<endl;
	for(int i3=0;i3<G.vexnum;i3++) {
		s=G.vertices[i3].firstarc;
		for(;s;s=s->nextarc) {
			cout<<setw(2)<<G.vertices[i3].data<<"      ";
			cout<<setw(2)<<s->adjvex<<"     ";
			cout<<setw(4)<<s->weight<<endl;
		}

	}
		
	cout<<"成功建立邻接表!"<<endl;
}

void AGraph::FMultiGraph(int k) {
	//cout<<"请输入多段图的段数:"<<endl;
	//cin>>k;
	cout<<"创建图G!"<<endl;
	ALGraph G;
	CreatAdjList(G);
	cout<<"开始找最短路径!"<<endl;
	int cost[N];
	int q;
	int d[N];
	int p[k];
	int j1=1;
	ArcNode *r;
	int c; // 存储最短路径长度
	//*cost=new int[N];
	//*d=new int[n];
	cost[N-1]=0; // cost[j] 记录结点j到汇点的最短路径长度
	d[N-1]=-1; // d[j] 记录结点j到汇点的最短路径上结点j的下一个结点
	for(int j=N-2;j>=0;j--) {
		int min=INF;
		for(r=G.vertices[j].firstarc;r;r=r->nextarc) {
			int v=r->adjvex;
			if(r->weight+cost[v]<min) {
				min=r->weight+cost[v];
				q=v;
			}
		}
		cost[j]=min;
		d[j]=q;
		j1++;
	}
	cout<<"找完了!"<<endl;
	p[0]=0;
	p[k-1]=N-1;
	c=cost[0];
	for(int j=1;j<=k-2;j++) {
		p[j]=d[p[j-1]];
	}
	cout<<"从源点到汇点的最短路径长度为: "<<c<<endl;
	cout<<"从源点到汇点的最短路径为: "<<endl;
	for(int b=0;b<k;b++) {
		cout<<p[b]<<" ";
	}
	cout<<endl;
}
