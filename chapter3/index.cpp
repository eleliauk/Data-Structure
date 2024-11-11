#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

struct Student {
    char id[9];                  // 学号（8位字符）
    char name[11];               // 姓名（10位字符）
    int scores[3];               // 各科成绩（例如：高等数学、数据结构、C++）
    int totalScore;              // 总成绩
    int time;                    // 所用时间（整型）
    Student* prev;               // 前驱指针
    Student* next;               // 后继指针
};

class DoublyCircularLinkedList {
public:
    Student* head;               // 链表头指针

    DoublyCircularLinkedList() : head(nullptr) {}

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
            cout << "学号: " << temp->id << ", 姓名: " << temp->name 
                 << ", 高等数学: " << temp->scores[0] 
                 << ", 数据结构: " << temp->scores[1] 
                 << ", C++: " << temp->scores[2]
                 << ", 总分: " << temp->totalScore
                 << ", 时间: " << temp->time << endl;
            temp = temp->next;
        } while (temp!= head);
    }
};

// 计算总成绩
void calculateTotalScore(Student* student) {
    student->totalScore = student->scores[0] + student->scores[1] + student->scores[2];
}

// 交换两个节点的数据
void swap(Student* a, Student* b) {
    char tempId[9], tempName[11];
    int tempScores[3], tempTotalScore, tempTime;

    strcpy(tempId, a->id);
    strcpy(tempName, a->name);
    memcpy(tempScores, a->scores, sizeof(a->scores));
    tempTotalScore = a->totalScore;
    tempTime = a->time;

    strcpy(a->id, b->id);
    strcpy(a->name, b->name);
    memcpy(a->scores, b->scores, sizeof(b->scores));
    a->totalScore = b->totalScore;
    a->time = b->time;

    strcpy(b->id, tempId);
    strcpy(b->name, tempName);
    memcpy(b->scores, tempScores, sizeof(tempScores));
    b->totalScore = tempTotalScore;
    b->time = tempTime;
}

// 快速排序的分区函数
Student* partition(Student* low, Student* high) {
    int pivotScore = high->totalScore;
    int pivotTime = high->time;
    Student* i = low->prev;

    for (Student* j = low; j!= high; j = j->next) {
        // 按总分降序，如果总分相同，按时间升序
        if (j->totalScore > pivotScore || (j->totalScore == pivotScore && j->time < pivotTime)) {
            i = (i == nullptr)? low : i->next;
            swap(i, j);
        }
    }
    i = (i == nullptr)? low : i->next;
    swap(i, high);
    return i;
}

// 快速排序函数
void quickSort(Student* low, Student* high) {
    if (high!= nullptr && low!= high && low!= high->next) {
        Student* pivot = partition(low, high);
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}

int main() {
    int n;
    DoublyCircularLinkedList list;
    ifstream inFile("input.txt"); // 假设数据文件名为 input.txt

    if (!inFile) {
        cerr << "无法打开文件" << endl;
        return 1;
    }

    inFile >> n;

    // 输入学生信息
    for (int i = 0; i < n; ++i) {
        Student* newStudent = new Student;
        inFile >> newStudent->id >> newStudent->name 
            >> newStudent->scores[0] >> newStudent->scores[1] >> newStudent->scores[2] 
            >> newStudent->time;
        
        newStudent->prev = newStudent->next = nullptr;
        
        // 计算总分并插入链表
        calculateTotalScore(newStudent);
        list.insert(newStudent);
    }

    inFile.close();

    // 排序
    if (list.head && list.head->next!= list.head) { // 确保链表不为空且有多个节点
        quickSort(list.head, list.head->prev);
    }

    // 输出排序后的学生信息
    cout << "\n排序后的学生信息：" << endl;
    list.printList();

    return 0;
}
