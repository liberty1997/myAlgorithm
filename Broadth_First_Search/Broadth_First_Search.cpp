//BFS的搜索路径不会根据邻接点的输入顺序变化而变化
//DFS的搜索路径会根据邻接点的输入顺序而变化
#include<iostream>
#include<iomanip>
#include<cstdlib>
#define MAX_VERTEX_NUM 40
using namespace std;

typedef struct ArcNode {
	int weight;
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode {
	ArcNode *firstarc;
	int data;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	int vexnum,arcnum;
	AdjList vertices;
}ALGraph;

//  以下是队列的数据结构
typedef struct QNode {
	int data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front; // 队头指针
	QueuePtr rear; // 队尾指针
}LinkQueue;

class Broadth_First_Search {
	private:
		int N; // 图的顶点数
		int *parent; // 存放当前结点在搜索路径中的前驱
		int *mark; // 标志数组
		void BFS(ALGraph &G, int u);
	public:
		Broadth_First_Search() {
			ALGraph G;
			CreatAdjList(G);
			BFS_Traversal(G);
		}
		void CreatAdjList(ALGraph &G);
		void BFS_Traversal(ALGraph &G);
		void InitQueue(LinkQueue &Q);
		int EnQueue(LinkQueue &Q, int e);
		int DeQueue(LinkQueue &Q);
		int QueueEmpty(LinkQueue &Q);
		int GetHead(LinkQueue &Q);
};

int main() {
	Broadth_First_Search A;
	return 0;
}

void Broadth_First_Search::CreatAdjList(ALGraph &G) {
	ArcNode *p;
	int m,n;
	cout<<"请输入图的顶点数和边数:(7 12)"<<endl;
	cin>>G.vexnum; cin>>G.arcnum; N=G.vexnum;
	cout<<"请输入顶点:(0~6)"<<endl;
	for(int i=0;i<G.vexnum;i++) {
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	cout<<"请输入每一条边的尾和头:"<<endl;
	cout<<"Example: 0 1, 1 6, 1 3, 1 2, 2 0,"<<endl;
	cout<<"         3 2, 3 0, 4 6, 4 5, 5 1, 6 5, 6 3"<<endl;
	for(int i=0;i<G.arcnum;i++) {
		cin>>m; cin>>n;
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=n;
		p->nextarc=G.vertices[m].firstarc;
		G.vertices[m].firstarc=p;
	}
}

void Broadth_First_Search::InitQueue(LinkQueue &Q) {
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) cout<<"InitQueue() Failed!"<<endl;
	Q.front->next=NULL;
}

int Broadth_First_Search::EnQueue(LinkQueue &Q, int e) {
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) cout<<"malloc for QueuePtr p Failed!"<<endl;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return e;
}

int Broadth_First_Search::DeQueue(LinkQueue &Q) {
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(Q.front==Q.rear) cout<<"队列为空!!!"<<endl;
	p=Q.front->next;
	int e;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return 0;
}

int Broadth_First_Search::QueueEmpty(LinkQueue &Q) {
	// 若队列为空,返回1,不空返回0
	if(Q.front==Q.rear) {
		cout<<"队列为空!!!"<<endl;
		return 1;
	}
	else {
		cout<<"队列不空!!!"<<endl;
		return 0;
	}
}

int Broadth_First_Search::GetHead(LinkQueue &Q) {
	QueuePtr p;
	int e;
	if(Q.front==Q.rear) cout<<"队列为空!!"<<endl;
	p=Q.front->next;
	e=p->data;
	return e;
}

void Broadth_First_Search::BFS_Traversal(ALGraph &G) {
	mark=new int[N];
	parent=new int[N];
	cout<<"BFS:"<<endl;
	for(int i=0;i<N;i++) {
		mark[i]=false;
		parent[i]=-1;
	}
	for(int u=0;u<N;u++) {
		if(mark[u]==false) {
			BFS(G,u);
		}
	}
	cout<<"BFS搜索结果为:"<<endl;
	for(int i=0;i<N;i++) {
		cout<<setw(2)<<G.vertices[i].data<<"  ";
	}
	cout<<endl;
	for(int i=0;i<N;i++) {
		cout<<setw(2)<<parent[i]<<"  ";
	}
	cout<<endl;
}

void Broadth_First_Search::BFS(ALGraph &G, int u) {
	LinkQueue Q;
	// 刚开始有错,因为没有调用InitQueue()
	InitQueue(Q);
	ArcNode *r;
	int E,k=0;
	mark[u]=true;
	EnQueue(Q,u);
	E=QueueEmpty(Q);
	while(E==0) {
		u=GetHead(Q);
		DeQueue(Q);
		for(r=G.vertices[u].firstarc;r;r=r->nextarc) {
			int v=r->adjvex;
			if(mark[v]==false) {
				mark[v]=true;
				parent[v]=u;
				EnQueue(Q,v);
			}
		}
		E=QueueEmpty(Q);
	}
}
