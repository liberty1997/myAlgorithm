// 所有被注释的cout都是用来调试的
#include<iostream>
#include<cstdlib>
#include<iomanip>
#define MAX_VERTEX_NUM 50
using namespace std;

typedef struct ArcSet {
	int point1;
	int point2;
	int weight;
}ArcSet, arcset[MAX_VERTEX_NUM];

class Graph {
	public:
		int Find(int p);
		//bool Connected(int p, int q);
		void Union(int p, int q);
		// 以上是并查集所需的函数
		void sink(int k);
		int delMin();
		void Swap(int &i, int &j);
		void Init(arcset &as);
		void Kruskal(arcset &as);
		Graph() {
			arcset as;
			Kruskal(as);
		}

	private:
		int *id; // 各结点的索引.初始时为自身,后续表示其所属连通分量中的根触点
		int count=0; // 每连接一条边,count就加1,当count==N-1时,说明已生成图的最小树
		int *Size; // 各个根结点对应的分量的大小
		// 以上是并查集所需的东西
		int N; // 图的结点数
		int *pq; // 优先队列/堆 存储边的权值
		int *index; // 建立边的索引,并保证随堆的结构变化,边的索引不会变
		int arcnum; // 边的数目

};

int main() {
	Graph G;
	return 0;
}

void Graph::Swap(int &i, int &j) {
	//cout<<"Swap-1"<<endl;
	int temp;
	temp=i;
	i=j;
	j=temp;
	//cout<<"Swap-2"<<endl;
}

int Graph::Find(int p) {
	//cout<<"Find-1"<<endl;
	// Find函数用来查找此触点的根触点
	// 当此触点的id值就是此触点时,直接返回此触点,即此触点的根触点就是它自己
	// 若此触点的id值不是它自己,即它不是自己的根触点,
	// 那就一直while追溯此触点的根触点,等找到后让函数返回根触点
	// (p==id[p]就表示此时找到的是根触点)
	while(p!=id[p]) {
		p=id[p];
	}
	//cout<<"Find-2"<<endl;
	return p;
}

// Connected函数用不着
/*
bool Graph::Connected(int p, int q) {
	// 判断结点p和q是否属于同一个连通分量/树
	// 用Find找到它俩的根触点后,若相等则表明二者处于同一个
	// 连通分量中,then 返回true,若不等,则它俩不处于同一个连通分量中
	//  then 返回false
	if(Find(p)==Find(q)) 
		return true;
	else
		return false;
} */

// 加入一条边时,先用Connected判断此边的两个
// 结点是否处于同一个连通分量,是的话就不加入了 以免形成回路
// 不是的话,就将这两个结点连通,即将这条边加入图的最小生成树
void Graph::Union(int p, int q) {
	int i=Find(p);
	int j=Find(q);
	//cout<<"Union-1"<<endl;
	if(i==j) {
		return; // 如果p q处于同一连通分量中,就不加入以免形成回路
	}
	// 若p q不处于同一连通分量的,就把它俩连通
	if(Size[i]<Size[j]) { // 总是选择将结点数量少的树加入到结点数量大的树上
		id[i]=j;		// 将小树的根合并到大树身上
		Size[j]+=Size[i];
		count++;
	}
	else {
		id[j]=i;
		Size[i]+=Size[j];
		count++;
	}
	cout<<"("<<p<<","<<q<<")"<<" ";
	//cout<<"Union-2"<<endl;
}

void Graph::sink(int k) {
	//cout<<"sink-1"<<endl;
	while(2*k<=N) {
		int j=2*k;
		if( j<N && pq[j+1]<pq[j] ) // 取较小的子结点
			j++;
		if(pq[k]<pq[j]) 
			break;
		Swap(pq[k],pq[j]);
		Swap(index[k],index[j]);
		k=j;
	}
	//cout<<"sink-2"<<endl;
}

// 此算法中没必要实现堆排序,
// 只要保证每次都能取到权值最小的边就行
// 正好delMin函数里每次取出最小值后 都会
// 进行堆的重构,保证堆有序
int Graph::delMin() {
	//cout<<"delMin-1"<<endl;
	int min=index[1]; // 取出堆顶(即权值最小的)元素,并把此边的索引返回min
	Swap(pq[1],pq[arcnum]);
	Swap(index[1],index[arcnum]);
	arcnum=arcnum-1;
	pq[arcnum+1]=-1;
	index[arcnum+1]=-1;
	sink(1);
	//cout<<"delMin-2"<<endl;
	return min;
}

void Graph::Init(arcset &as) {
	//cout<<"Init-1"<<endl;
	cout<<"请输入顶点个数和边的个数:(6 10)"<<endl;
	cin>>N; cin>>arcnum;
	cout<<"请输入边的两个结点及权值："<<endl;
	cout<<"Example: 0 1 6, 0 2 1, 0 3 5, 1 2 5, 2 3 5,"<<endl;
	cout<<"         1 4 3, 3 5 2, 4 5 6, 2 4 6, 2 5 4"<<endl;
	for(int i=1;i<arcnum+1;i++) {
		cin>>(as[i].point1);
		cin>>(as[i].point2);
		cin>>(as[i].weight);
	}
	pq=new int[arcnum+1];
	index=new int[arcnum+1];
	id=new int[N];
	Size=new int[N+1];
	pq[0]=-1;
	for(int i=0;i<N;i++) {
		id[i]=i;
		Size[i]=1;
	}
	for(int i=1;i<arcnum+1;i++) {	
		pq[i]=(as[i].weight);
		index[i]=i;
	}
	/*
	for(int j=0;j<arcnum+1;j++) {
	 cout<<pq[j]<<" ";
	} */
	// 上面对pq数组初始化
	// 接下来先把pq数组进行堆有序操作
	for(int k=N/2;k>=1;k--) {
		sink(k);
	}
	//cout<<"Init-2"<<endl;
	//cout<<"pq[1]="<<pq[1]<<endl;
}

void Graph::Kruskal(arcset &as) {
	//cout<<"Kruskal-1"<<endl;
	int mmin;
	Init(as);
	for(int i=0;i<N;i++) {
		mmin=delMin();
		//cout<<"mmin="<<mmin<<endl;
		Union(as[mmin].point1,as[mmin].point2);
	}
	cout<<endl;
	//cout<<"Kruskal-2"<<endl;
}
