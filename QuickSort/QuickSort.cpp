#include<iostream>
#include<cstdlib>
#define LIST_INIT_SIZE 300
#define INCREMENT 10
using namespace std;
typedef int ElemType;

typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

// template <class T>
class SortableList{
	public:
		SqList L;
		int nu; // the number of SqList's elements
		void QuickSort();
		int Partition(int left, int right);
		void Swap(int &i, int &j);
		void CreatSqList();
		//int Visit();
		void Display();
		SortableList() {
			CreatSqList();
		}
	private:
		void QuickSort(int left, int right);
};

int main() {
	SortableList A;
	A.QuickSort();
	SortableList B;
	B.QuickSort();
	return 0;
}

// Creat_SqList
void SortableList::CreatSqList() {
	//SqList L;
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) cout<<"MALLOC_FAILED!"<<endl;
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	int i1,i2;//zong为随即生成的线性表的元素个数
	do{
		nu=rand()%31;
	}while(nu<9);
	for(i1=0;i1<nu;i1++) {
		L.elem[i1]=rand()%500;
		L.length++;
	}
	L.elem[nu+1]=65535;
	L.length++;
	cout<<endl<<"A initial SqList:"<<endl;
	for(i2=0;i2<nu;i2++) {
		cout<<L.elem[i2]<<" ";
	}
	cout<<endl<<"L.length:"<<L.length<<endl;
}
// Swap
void SortableList::Swap(int &i, int &j) {
	int temp;
	temp=i;
	i=j;
	j=temp;
}
// Partition
int SortableList::Partition(int left, int right) {
	// Premise: left<=right
	int i=left, j=right+1;
	do{
		do i++; while(L.elem[i]<L.elem[left]);
		do j--; while(L.elem[j]>L.elem[left]);
		if(i<j) Swap(L.elem[i],L.elem[j]);
	}while(i<j);
	Swap(L.elem[left],L.elem[j]);
	return j;
}
// QuickSort(int left, int right)
void SortableList::QuickSort(int left, int right) {
	if(left<right) {
		int j=Partition(left,right);
		QuickSort(left,j-1);
		QuickSort(j+1,right);
	}
}
// QuickSort()
void SortableList::QuickSort() {
	QuickSort(0,nu-1);
	Display();
}
// Display()
void SortableList::Display() {
	int i3;
	cout<<"THE Sorted SqList:"<<endl;
	for(i3=0;i3<nu;i3++) {
		cout<<L.elem[i3]<<" ";
	}
	cout<<endl;
}
