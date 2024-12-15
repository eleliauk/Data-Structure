#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 构建二叉树函数
TreeNode* createTree(const vector<pair<int, int>>& num, int idx) {
    if (idx == -1) return NULL; // -1 表示无子结点
    TreeNode* root = new TreeNode(idx + 1);
    if (num[idx].first != 0) { // 左子结点非空
        root->left = createTree(num, num[idx].first - 1);
    }
    if (num[idx].second != 0) { // 右子结点非空
        root->right = createTree(num, num[idx].second - 1);
    }
    return root;
}

// 前序遍历
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// 中序遍历
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// 后序遍历
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> num(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        num[i] = {l, r};
    }
    TreeNode* root = createTree(num, 0);

    // 前序遍历
    preorder(root);
    cout << endl;

    // 中序遍历
    inorder(root);
    cout << endl;

    // 后序遍历
    postorder(root);
    cout << endl;

    return 0;
}