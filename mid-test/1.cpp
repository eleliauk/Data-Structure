#include <iostream>
#include<algorithm>
using namespace std;
bool compared(int a,int b){
    return a>b;
}
int Merge(int a[], int b[],int c[]){
    for(int i=0;i<10;i++){
        c[i]=a[i];
    };
    for(int j=10;j<20;j++){
        c[j]=b[j-10];
    }
    sort(c,c+20,compared);
    int len=1;
    for(int i=0;i<20;i++){
        if(c[i]!=c[i+1]){
            len++;
        }
    }
    return len;
};
int main() {
    int a[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int b[10] = {10, 12, 12, 12, 18, 11, 13, 15, 17, 19};
    int c[20];

    // 调用 Merge 函数
    int uniqueLength = Merge(a, b, c);

    // 输出去重后的长度
    cout << "去重后的元素个数: " << uniqueLength << endl;

    // 输出去重后的数组内容
    cout << "去重后的数组内容: ";
    for (int i = 0; i < 20; i++) {
        if (i == 0 || c[i] != c[i - 1]) {
            cout << c[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
