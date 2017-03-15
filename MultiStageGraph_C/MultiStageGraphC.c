// 这个求出来是0 1 6 9 11, C++ 那个求出来是0 2 5 9 11
#include<stdio.h>
#include<stdlib.h>
#define INF 999
#define MAX_VERTEX_NUM 30

//边结点
typedef struct ArcNode {
	int adjvex;
	int weight;
	struct ArcNode *nextarc;
}ArcNode;

//头结点
typedef struct VNode {
	int data;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

//图
typedef struct {
	AdjList vertices;
	int vexnum,arcnum;
}AGraph;

int main() {
	AGraph G;
	ArcNode *s,*r;
	int m,n,c,q,N;
	int k=5; // 五段图
	printf("请输入顶点数和边数:(12 21)\n");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	N=G.vexnum;
	printf("请输入顶点:(0~11)\n");
	for(int i=0;i<G.vexnum;i++) {
		scanf("%d",&G.vertices[i].data);
		G.vertices[i].firstarc=NULL;
	}
	printf("请输入边的尾和头及其权值:\n");
	printf("Example:0 4 2, 0 3 3, 0 2 7, 0 1 9, 1 7 1, 1 6 2, 1 5 4, 2 6 7, 2 5 2, 3 7 11,\n");
	printf("        4 7 8, 4 6 11, 5 9 5, 5 8 6, 6 9 3, 6 8 4, 7 10 6, 7 9 5, 8 11 4, 9 11 2, 10 11 5\n");
	// 建立邻接表
	for(int i=0;i<G.arcnum;i++) {
		// 生成空空的新结点
		s=(ArcNode *)malloc(sizeof(ArcNode));
		scanf("%d %d %d",&m,&n,&s->weight);
		s->adjvex=n; // 将邻接点的位置信息给了新结点
		// 下两行是将邻接点插入邻接表(单链表)头部的过程
		s->nextarc=G.vertices[m].firstarc;
		G.vertices[m].firstarc=s;
	}
	int cost[N];
	int d[N];
	int p[k]; // 存储最优决策序列, 即各个状态的最优解
	cost[N-1]=0; // cost[j]记录结点j到汇点的最短路径长度
	d[N-1]=0; // d[j]记录结点j到汇点的最短路径上j的下一个结点
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
	}
	p[0]=0;
	p[k-1]=N-1;
	c=cost[0];
	for(int j=1;j<=k-2;j++) {
		p[j]=d[p[j-1]];
	}
	printf("从源点到汇点的最短路径长度为:%d\n",c);
	printf("从源点到汇点的最短路径为:");
	for(int b=0;b<k;b++) {
		printf(" %d",p[b]);
	}
	printf("\n");
	return 0;
}
