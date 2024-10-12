#include <iostream>
using namespace std;

// 定义节点结构
struct Node {
    int data;
    Node* next;
};

// 有序链表类
class OrderedList {
private:
    Node* head;
    
public:
    OrderedList() {
        head = nullptr;
    }

    // 析构函数
    ~OrderedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 添加元素到链表，保持有序
    void AddElem(int elem) {
        Node* newNode = new Node{ elem, nullptr};
        
        if (head == nullptr || head->data > elem) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next != nullptr && curr->next->data < elem) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }

    // 删除元素
    void DelElem(int elem) {
        if (head == nullptr) return;

        if (head->data == elem) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* curr = head;
        while (curr->next != nullptr && curr->next->data != elem) {
            curr = curr->next;
        }
        if (curr->next != nullptr) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
    }

    // 打印链表
    void Print() const {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // 获取链表头部
    Node* GetHead() const {
        return head;
    }
};
class Set {
private:
    OrderedList list;

public:
    // 添加元素到集合
    void AddElem(int elem) {
        list.AddElem(elem);
    }

    // 删除集合中的元素
    void DelElem(int elem) {
        list.DelElem(elem);
    }

    // 并集操作
    static Set Union(const Set& s1, const Set& s2) {
        Set result;
        Node* curr1 = s1.list.GetHead();
        Node* curr2 = s2.list.GetHead();

        // 合并两个有序链表
        while (curr1 != nullptr && curr2 != nullptr) {
            if (curr1->data < curr2->data) {
                result.AddElem(curr1->data);
                curr1 = curr1->next;
            } else if (curr1->data > curr2->data) {
                result.AddElem(curr2->data);
                curr2 = curr2->next;
            } else {
                result.AddElem(curr1->data);
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }

        // 处理剩余元素
        while (curr1 != nullptr) {
            result.AddElem(curr1->data);
            curr1 = curr1->next;
        }

        while (curr2 != nullptr) {
            result.AddElem(curr2->data);
            curr2 = curr2->next;
        }

        return result;
    }

    // 交集操作
    static Set Intersection(const Set& s1, const Set& s2) {
        Set result;
        Node* curr1 = s1.list.GetHead();
        Node* curr2 = s2.list.GetHead();

        while (curr1 != nullptr && curr2 != nullptr) {
            if (curr1->data < curr2->data) {
                curr1 = curr1->next;
            } else if (curr1->data > curr2->data) {
                curr2 = curr2->next;
            } else {
                result.AddElem(curr1->data);
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }

        return result;
    }

    // 差集操作
    static Set Difference(const Set& s1, const Set& s2) {
        Set result;
        Node* curr1 = s1.list.GetHead();
        Node* curr2 = s2.list.GetHead();

        while (curr1 != nullptr) {
            if (curr2 == nullptr || curr1->data < curr2->data) {
                result.AddElem(curr1->data);
                curr1 = curr1->next;
            } else if (curr1->data > curr2->data) {
                curr2 = curr2->next;
            } else {
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }

        return result;
    }

    // 打印集合中的元素
    void Print() const {
        list.Print();
    }
};
int main() {
    Set set1, set2;
    
    // 输入集合1
    set1.AddElem(3);
    set1.AddElem(5);
    set1.AddElem(6);
    set1.AddElem(9);
    set1.AddElem(10);
    set1.AddElem(12);
    set1.AddElem(27);
    set1.AddElem(35);
    set1.Print(); // 输出集合1

    // 输入集合2
    set2.AddElem(5);
    set2.AddElem(8);
    set2.AddElem(10);
    set2.AddElem(12);
    set2.AddElem(27);
    set2.AddElem(31);
    set2.AddElem(42);
    set2.AddElem(51);
    set2.AddElem(55);
    set2.AddElem(63);
    set2.Print(); // 输出集合2

    // 求并集
    Set unionSet = Set::Union(set1, set2);
    cout << "Union: ";
    unionSet.Print();

    // 求交集
    Set intersectionSet = Set::Intersection(set1, set2);
    cout << "Intersection: ";
    intersectionSet.Print();

    // 求差集
    Set differenceSet = Set::Difference(set1, set2);
    cout << "Difference: ";
    differenceSet.Print();

    return 0;
}