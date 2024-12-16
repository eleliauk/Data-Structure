#include <iostream>
using namespace std;
#define endl '\n'
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
void countLeaves(TreeNode* node, int x, int& count, TreeNode* parent = nullptr) {
    if (!node) return;
    if (!node->left && !node->right && node->val < x) {
        count++;
        if (parent) {
            cout << "叶子节点是 " << node->val << " 双亲节点是 " << parent->val << endl;
        }
    }
    countLeaves(node->left, x, count, node);
    countLeaves(node->right, x, count, node);
}

int main() {
    //       5
    //      / \
    //     3   8
    //    / \   \
    //   1   4   9
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(9);

    int x ; 
    cout << "输入要查找的定值 X: ";
    cin >> x;
    int count = 0;
    countLeaves(root, x, count);

    cout << " 小于定值 " << x << " 有 " << count <<" 个 "<< endl;
    return 0;
}