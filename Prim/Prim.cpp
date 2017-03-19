// Prim:邻接表存储
// 仅考虑了局部最优性,只能保证
// 从某个源点出发得到一棵生成树,
// 但不一定是最小代价生成树
#include<iostream>
#include<iomanip>
#define MAX_VERTEX_NUM 30
#define INF 999
using namespace std;

typedef struct ArcNode {
	int weight;
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode {
	int data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	int vexnum,arcnum;
	AdjList vertices;
}ALGraph;

class Graph {
	private:
		int N;
		void Prim(ALGraph &G, int *nearest, int *lowcost);
	public:
		void CreatAdjList(ALGraph &G);
		void Prim(ALGraph &G);
		Graph() {
			ALGraph G;
			CreatAdjList(G);
			Prim(G);
		}
};

int main() {
	Graph A;
	return 0;
}

void Graph::CreatAdjList(ALGraph &G) {
	ArcNode *e;
	int m,n,q;
	cout<<"构造带权无向连通图的邻接表:"<<endl;
	cout<<"输入图的顶点数和边数:(6 10)"<<endl;
	cin>>G.vexnum; cin>>G.arcnum; N=G.vexnum;
	cout<<"请输入顶点:(0~5)"<<endl;
	for(int i=0;i<G.vexnum;i++) {
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	cout<<"请输入边的顶点及权值:"<<endl;
	cout<<"Example: 0 1 6, 0 2 1, 0 3 5, 1 2 5, 2 3 5, 1 4 3,"<<endl;
	cout<<"         3 5 2, 4 5 6, 2 4 6, 2 5 4"<<endl;
	for(int i=0;i<G.arcnum;i++) {
		cin>>m; cin>>n; cin>>q;
		e=(ArcNode *)malloc(sizeof(ArcNode));
		e->adjvex=n;
		e->weight=q;
		e->nextarc=G.vertices[m].firstarc;
		G.vertices[m].firstarc=e;

		e=(ArcNode *)malloc(sizeof(ArcNode));
		e->adjvex=m;
		e->weight=q;
		e->nextarc=G.vertices[n].firstarc;
		G.vertices[n].firstarc=e;
		// 以上两段为建立邻接表 的单链表
		// 因为是无向图,所以连通的结点之间
		// 是互相有路径的,所以上面有两段
		// 有向图的话只需要一段
	}
	cout<<"已为带权无向连通图建立了邻接表!"<<endl;
}

void Graph::Prim(ALGraph &G) {
	int *nearest=new int[N];
	int *lowcost=new int[N];
	// nearest[v]=u 表示在生成最小生成树的路径上u是v的前驱 || u是边(u,v)在生成树上的端点
	// lowcost[j]中存储结点j与当前生成树中的结点之间的最短路径
	Prim(G, nearest,lowcost);
	for(int j=0;j<N;j++) {
		cout<<"("<<nearest[j]<<","<<j<<","<<lowcost[j]<<")";
	}
	cout<<endl;
	delete []nearest;
	delete []lowcost;
}

void Graph::Prim(ALGraph &G, int *nearest, int *lowcost) {
	bool *mark=new bool[N]; // mark数组用来标记当前结点是否已经加入最小生成树
	ArcNode *p;
	int k,k1;
	cout<<"请输入源点:(0~5)"<<endl;
	cin>>k;
	k1=k;
	if(k<0||k>N-1) cout<<"OutOfBounds!!!"<<endl;
	for(int i=0;i<N;i++) {
		nearest[i]=-1;
		mark[i]=false;
		lowcost[i]=INF;
	}
	// 初始化与源点k相关的信息
	lowcost[k]=0;
	nearest[k]=k;
	mark[k]=true; // 将源点k加入生成树
	for(int i=1;i<N;i++) {
		if(i!=k1) {
			// 每次从上次加入生成树的
			// 结点继续寻找下一个符合要求的
			// 生成树结点时就更新lowcost和nearest
			for(p=G.vertices[k].firstarc;p;p=p->nextarc) {
				int j=p->adjvex;
				if((!mark[j])&&(p->weight<lowcost[j])) {
					lowcost[j]=p->weight;
					nearest[j]=k;
				}	
			}
			// 从刚加入生成树的结点的
			// 不属于生成树的邻接点中
			// 选出一个路径最短
			int min=INF;
			for(int j=0;j<N;j++) {
				if((!mark[j])&&(lowcost[j]<min)) {
					min=lowcost[j];
					k=j;
				}
			}
			// 选完后将其加入生成树
			mark[k]=true;
		}
	}
}
