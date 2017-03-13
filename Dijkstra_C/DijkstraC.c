#include<stdio.h>
#define MAX_VERTEX_NUM 20
#define INF 999

typedef struct ArcCell {
	int weight;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	int vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;

//int Choose(int *d, bool *s);

int main() {
	MGraph G;
	int a,b,c=0;
	int s; //存储源点
	printf("输入顶点个数和边数:\n");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	printf("输入顶点:\n");
	for(int i=0;i<G.vexnum;i++) {
		scanf("%d",&G.vexs[i]);
	}
	// 初始化邻接矩阵
	for(int i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			G.arcs[i][j].weight=INF;
		}
	}
	printf("输入弧的两个顶点及其权值:\n");
	printf("Example: 0 1 50, 0 2 10, 0 4 70, 1 2 15, 1 4 10,\n");
	printf("         2 0 20, 2 3 15, 3 1 20, 3 4 35, 4 3 30, 5 3 3\n");
	for(int i=0;i<G.arcnum;i++) {
		scanf("%d %d",&a,&b);
		scanf("%d",&G.arcs[a][b].weight);
	}		
	printf("当前顶点数和边数:%d %d\n",G.vexnum,G.arcnum);
	printf("当前顶点:");
	for(int i=0;i<G.vexnum;i++) {
		printf("%d ",G.vexs[i]);
	}
	printf("\n当前图的邻接矩阵:\n");
	for(int i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			printf("%3d  ",G.arcs[i][j].weight);
			c++;
			if(c%G.vexnum==0) printf("\n");
		}
	}
	// 以上是建立图的邻接矩阵,虽然写的不好，但能正常运行,勿改
	while(1) {
	printf("输入源点:\n");
	scanf("%d",&s);
	int d[G.vexnum]; // 存储最短路径
	int path[G.vexnum]; // 存储路径_顶点前驱
	int inS[G.vexnum]; //判断顶点是否在S中,即判断当前顶点是否已求得最小路径
	int k,min,minpos;
	//初始化d和path和inS数组
	for(int i=0;i<G.vexnum;i++) {
		d[i]=G.arcs[s][i].weight;
		inS[i]=0;
		if(i!=s && d[i]<INF)
			path[i]=s;
		else
			path[i]=-1;
	}
	//已选源点后,对源点相关进行操作
	inS[s]=1; // 将源点加入S
	d[s]=0; // 源点到自身的距离设为0
	for(int i=1;i<G.vexnum-1;i++) {
		min=INF;
		minpos=-1;
		for(int i1=0;i1<G.vexnum;i1++) {
			if(inS[i1]==0 && d[i1]<min) {
				min=d[i1];
				minpos=i1;
			}
		}	
		k=minpos;
		inS[k]=1;
		for(int j=0;j<G.vexnum;j++) {
			if(inS[j]==0 && d[k]+G.arcs[k][j].weight<d[j]) {
				d[j]=d[k]+G.arcs[k][j].weight;
				path[j]=k;
			}
		}
	}
	printf("vexs   | 最短路径 | 前驱\n");
	for(int m=0;m<G.vexnum;m++) {
		if(m!=s) printf("%d      |  ",m);
		if(m!=s) printf("%4d    | ",d[m]);
		if(m!=s) printf("%2d\n",path[m]);
	}
	printf("\n");
	printf("\n---------------------");
	printf("\n   退出请按 Ctrl+C ");
	printf("\n---------------------");
	printf("\n");
	}
	
	return 0;
}
