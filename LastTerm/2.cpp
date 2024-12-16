#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
ListNode* createList() {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int num;
    cout << "输入单链表的元素 (输入-1结束): ";
    while (cin >> num && num != -1) {
        ListNode* newNode = new ListNode(num);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        tail->next = head;
    }
    return head;
}
ListNode* mergeLists(ListNode* list1, ListNode* list2) {
    ListNode* tail1 = list1;
    ListNode* tail2 = list2;
    while (tail1->next != list1) tail1 = tail1->next;
    while (tail2->next != list2) tail2 = tail2->next;
    tail1->next = list2;
    tail2->next = list1;
    return list1;
}

int countNodes(ListNode* head) {
    int count = 0;
    ListNode* current = head;
    do {
        count++;
        current = current->next;
    } while (current != head);
    return count;
}
int coutX(ListNode* head, int x) {
    int count = 0;
    ListNode* current = head;
    do {
        if (current->val == x) count++;
        current = current->next;
    } while (current != head);
    return count;
}
int main() {
    ListNode* list1 = createList();
    ListNode* list2 = createList();

    int x;
    cout << "输入要查找的定值 X: ";
    cin >> x;
    ListNode* mergedList = mergeLists(list1, list2);
    int count = countNodes(mergedList);
    cout << "合并后的单链表中结点个数: " << count << endl;
    cout<< " 等于 " << x << " 有 " << coutX(mergedList, x) << " 个 "<< endl;

    return 0;
}