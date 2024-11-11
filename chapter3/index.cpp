#include <iostream>
#include <string>
using namespace std;

struct Student {
    char id[9];         // 学号（8位字符）
    char name[11];      // 姓名（10位字符）
    int score;          // 成绩（整型）
    int time;           // 所用时间（整型）
    Student* prev;      // 前驱指针
    Student* next;      // 后继指针
};
class DoublyCircularLinkedList {
public:
    Student* head;  // 链表头指针

    DoublyCircularLinkedList() {
        head = nullptr;
    }

    // 插入学生信息节点
    void insert(Student* newStudent) {
        if (!head) {
            head = newStudent;
            newStudent->next = head;
            newStudent->prev = head;
        } else {
            Student* tail = head->prev;  // 获取尾部节点
            tail->next = newStudent;
            newStudent->prev = tail;
            newStudent->next = head;
            head->prev = newStudent;
        }
    }

    // 打印链表中的学生信息
    void printList() {
        if (!head) return;
        Student* temp = head;
        do {
            cout << "ID: " << temp->id << ", Name: " << temp->name 
                 << ", Score: " << temp->score << ", Time: " << temp->time << endl;
            temp = temp->next;
        } while (temp != head);
    }
};
void swap(Student* a, Student* b) {
    // 交换两个节点的数据
    char tempId[9], tempName[11];
    int tempScore, tempTime;

    strcpy(tempId, a->id);
    strcpy(tempName, a->name);
    tempScore = a->score;
    tempTime = a->time;

    strcpy(a->id, b->id);
    strcpy(a->name, b->name);
    a->score = b->score;
    a->time = b->time;

    strcpy(b->id, tempId);
    strcpy(b->name, tempName);
    b->score = tempScore;
    b->time = tempTime;
}

Student* partition(Student* low, Student* high) {
    int pivotScore = high->score;
    int pivotTime = high->time;
    Student* i = low->prev;

    for (Student* j = low; j != high; j = j->next) {
        // 按成绩降序，如果成绩相同，按时间升序
        if (j->score > pivotScore || (j->score == pivotScore && j->time < pivotTime)) {
            i = (i == nullptr) ? low : i->next;
            swap(i, j);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i, high);
    return i;
}
void quickSort(Student* low, Student* high) {
    if (high != nullptr && low != high && low != high->next) {
        Student* pivot = partition(low, high);
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}
