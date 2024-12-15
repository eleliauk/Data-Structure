#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// 域名树节点结构
struct DomainNode {
    string name;  // 节点名称
    vector<DomainNode*> children;  // 子节点指针数组
    
    DomainNode(string n) : name(n) {}
};

class DomainTree {
private:
    DomainNode* root;
    
    // 分割域名字符串
    vector<string> splitDomain(string domain) {
        vector<string> parts;
        string part;
        for (int i = domain.length() - 1; i >= 0; i--) {
            if (domain[i] == '.') {
                if (!part.empty()) {
                    parts.push_back(part);
                    part = "";
                }
            } else {
                part = domain[i] + part;
            }
        }
        if (!part.empty()) {
            parts.push_back(part);
        }
        return parts;
    }
    
    // 递归打印树结构
    void printTree(DomainNode* node, string prefix = "", bool isLast = true) {
        if (!node) return;
        
        cout << prefix;
        if (isLast) {
            cout << "└───";
            prefix += "    ";
        } else {
            cout << "├───";
            prefix += "│   ";
        }
        cout << node->name << endl;
        
        for (size_t i = 0; i < node->children.size(); i++) {
            printTree(node->children[i], prefix, i == node->children.size() - 1);
        }
    }
    
    // 递归查找域名
    bool searchDomain(DomainNode* node, const vector<string>& parts, int index) {
        if (index >= parts.size()) return true;
        
        for (DomainNode* child : node->children) {
            if (child->name == parts[index]) {
                return searchDomain(child, parts, index + 1);
            }
        }
        return false;
    }
    
    // 递归删除树
    void deleteTree(DomainNode* node) {
        if (!node) return;
        for (DomainNode* child : node->children) {
            deleteTree(child);
        }
        delete node;
    }

public:
    DomainTree() {
        root = new DomainNode("root");
    }
    
    ~DomainTree() {
        deleteTree(root);
    }
    
    // 插入域名
    void insert(string domain) {
        vector<string> parts = splitDomain(domain);
        DomainNode* current = root;
        
        for (const string& part : parts) {
            bool found = false;
            for (DomainNode* child : current->children) {
                if (child->name == part) {
                    current = child;
                    found = true;
                    break;
                }
            }
            if (!found) {
                DomainNode* newNode = new DomainNode(part);
                current->children.push_back(newNode);
                current = newNode;
            }
        }
    }
    
    // 显示整个树结构
    void display() {
        cout << "树结构为" << endl;
        printTree(root);
    }
    
    // 查询域名是否存在
    bool search(string domain) {
        vector<string> parts = splitDomain(domain);
        return searchDomain(root, parts, 0);
    }
    
    // 从文件加载域名
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string domain;
        while (getline(file, domain)) {
            if (!domain.empty()) {
                insert(domain);
            }
        }
        file.close();
    }
    
    // 保存域名到文件
    void saveToFile(const string& filename) {
        ofstream file(filename);
        // TODO: 实现保存功能
        file.close();
    }
};

int main() {
    DomainTree tree;
    
    // 从文件加载域名
    tree.loadFromFile("domains.txt");
    
    while (true) {
        cout << "\n域名树操作菜单：" << endl;
        cout << "1. 显示域名树" << endl;
        cout << "2. 添加域名" << endl;
        cout << "3. 查询域名" << endl;
        cout << "4. 退出" << endl;
        
        int choice;
        cout << "请选择操作 (1-4): ";
        cin >> choice;
        
        if (choice == 1) {
            tree.display();
        }
        else if (choice == 2) {
            string domain;
            cout << "请输入要添加的域名: ";
            cin >> domain;
            tree.insert(domain);
            cout << "域名已添加！" << endl;
        }
        else if (choice == 3) {
            string domain;
            cout << "请输入要查询的域名: ";
            cin >> domain;
            if (tree.search(domain)) {
                cout << "域名存在！" << endl;
            } else {
                cout << "域名不存在！" << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "无效的选择，请重试！" << endl;
        }
    }
    
    return 0;
}
