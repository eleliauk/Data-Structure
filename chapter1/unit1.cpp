//
// Created by 单禹嘉 on 24-9-23.
//10.4.1 含并交和差运算的集合类型
#include <iostream>
using namespace std;
//元素类型 结点类型和指针类型
typedef int ElementType;
typedef struct NodeType {
    ElementType data;
    NodeType * next;
}NodeType,*LinkType;
//有序表类型
typedef struct {
    LinkType head,tail;
    int size;
    int curpos;
    LinkType current;
}OrderedList;

