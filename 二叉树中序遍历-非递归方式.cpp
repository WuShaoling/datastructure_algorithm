#include<iostream>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//�ǵݹ鷽ʽ
void inOrderRecur(TreeNode* tree) {
    if(NULL == tree)
        return;
    stack<TreeNode*> ss;
    while(!ss.empty() || tree) {
        if(NULL != tree) {
            while(tree) {
                ss.push(tree);
                tree = tree->left;
            }
        } else {
            TreeNode *tree = ss.top();
            ss.pop();
            cout << tree->val;
            tree = tree->right;
        }
    }
}

//�ݹ鷽ʽ
void inOrderRecur1(TreeNode* tree) {
    if(NULL == tree)
        return;
    inOrderRecur1(tree->left);
    cout << tree->val << " ";
    inOrderRecur1(tree->right);
}

int main() {
    return 0;
}

