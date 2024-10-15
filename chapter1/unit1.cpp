#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class OrderedList {
private:
    Node* head;
    
public:
    OrderedList() {
        head = nullptr;
    }

    ~OrderedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

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

    void Print() const {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    Node* GetHead() const {
        return head;
    }
};

class Set {
private:
    OrderedList list;

public:

    void AddElem(int elem) {
        list.AddElem(elem);
    }

    void DelElem(int elem) {
        list.DelElem(elem);
    }

    static Set Union(const Set& s1, const Set& s2) {
        Set result;
        Node* curr1 = s1.list.GetHead();
        Node* curr2 = s2.list.GetHead();

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

    void Print() const {
        list.Print();
    }
};

int main() {
    Set set1, set2;
    int numElems, elem;

    cout << "请输入集合1的元素个数：";
    cin >> numElems;
    cout << "请输入集合1的元素：";
    for (int i = 0; i < numElems; ++i) {
        cin >> elem;
        set1.AddElem(elem);
    }
    cout << "集合1：";
    set1.Print();

    // 输入集合2
    cout << "请输入集合2的元素个数：";
    cin >> numElems;
    cout << "请输入集合2的元素：";
    for (int i = 0; i < numElems; ++i) {
        cin >> elem;
        set2.AddElem(elem);
    }
    cout << "集合2：";
    set2.Print();

    // 计算并集
    Set unionSet = Set::Union(set1, set2);
    cout << "并集：";
    unionSet.Print();

    // 计算交集
    Set intersectionSet = Set::Intersection(set1, set2);
    cout << "交集：";
    intersectionSet.Print();

    // 计算差集
    Set differenceSet = Set::Difference(set1, set2);
    cout << "差集：";
    differenceSet.Print();

    return 0;
}