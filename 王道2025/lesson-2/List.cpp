#include <iostream>

using namespace std;

typedef int ElemType;
#define InitSize 100
typedef struct {
    ElemType *data;
    int MaxSize,length;
} SqList;
void InitList(SqList &L){
    L.length=0;
    L.data=new ElemType[InitSize];
    L.MaxSize=InitSize;
}
bool ListInsert(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1)
        return false;
    if(L.length>=L.MaxSize)
        return false;
    for(int j=L.length;j>=i;j--)
        L.data[j]=L.data[j-1];
    L.data[i-1]=e;
    L.length++;
    return true;
}
bool ListDelete(SqList &L,int i,ElemType &e){
    if(i<1||i>L.length)
        return false;
    e=L.data[i-1];
    for(int j=i;j<L.length;j++)
        L.data[j-1]=L.data[j];
    L.length--;
    return true;
}
int LocalSearch(SqList L,ElemType key){
    for(int i=0;i<L.length;i++)
        if(L.data[i]==key)
            return i+1;
    return 0;
}
