// 搜索结果根据输入的邻接点的顺序会变
// -1 0 3 6 -1 6 1 and -1 0 1 1 -1 6 1
#include<iostream>
#include<iomanip>
#define MAX_VERTEX_NUM 40
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

class Depth_First_Search {
	private:
		int N; // 图的顶点数目
		int *parent;
		int *mark;
		void DFS(ALGraph &G, int u);
	public:
		Depth_First_Search() {
			ALGraph G;
			CreatAdjList(G);
			DFS_Traversal(G);
		}
		void CreatAdjList(ALGraph &G);
		void DFS_Traversal(ALGraph &G);

};

int main()
{
	Depth_First_Search A;
	return 0;
}

void Depth_First_Search::CreatAdjList(ALGraph &G) {
	ArcNode *p;
	int m,n;
	cout<<"请输入顶点数和边数:(7 12)"<<endl;
	cin>>G.vexnum; cin>>G.arcnum; N=G.vexnum;
	cout<<"请输入顶点:(0~6)"<<endl;
	for(int i=0;i<G.vexnum;i++) {
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	cout<<"请输入每一条弧的尾和头:"<<endl;
	cout<<"Example: 0 1, 1 6, 1 3, 1 2, 2 0, 3 2,"<<endl;
	cout<<"3 0, 4 6, 4 5, 5 1, 6 5, 6 3"<<endl;
	for(int i=0;i<G.arcnum;i++) {
		cin>>m; cin>>n;
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=n;
		p->nextarc=G.vertices[m].firstarc;
		G.vertices[m].firstarc=p;
	}
	cout<<"以上为建立邻接表!"<<endl;
}

void Depth_First_Search::DFS_Traversal(ALGraph &G) {
	mark=new int[N];
	parent=new int[N];
	cout<<"DFS:"<<endl;
	for(int i=0;i<N;i++) {
		mark[i]=false;
		parent[i]=-1;
	}
	for(int u=0;u<N;u++) {
		if(mark[u]==false) {
			DFS(G,u);
		}
	}
	cout<<"DFS搜索结果为:"<<endl;
	for(int j=0;j<N;j++) {
		cout<<setw(2)<<j<<"  ";
	}
	cout<<endl;
	for(int j=0;j<N;j++) {
		cout<<setw(2)<<parent[j]<<"  ";
	}
	cout<<endl;
}

void Depth_First_Search::DFS(ALGraph &G, int u) {
	mark[u]=true;
	ArcNode *r;
	for(r=G.vertices[u].firstarc;r;r=r->nextarc) {
		int v=r->adjvex;
		if(mark[v]==false) {
			parent[v]=u;
			DFS(G,v);
		}
	}
}
