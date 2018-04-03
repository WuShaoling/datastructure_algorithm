#include<iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(s == NULL)
            return false;
        if(s->val == t->val && isTheSame(s, t))
            return true;
        else
            return isSubtree(s->left, t) || isSubtree(s->right, t);
        return false;
    }

    bool isTheSame(TreeNode* s, TreeNode* t) {
        ///������ͬʱ����׶ˣ�˵����ȫ���
        if(s == NULL && t == NULL)
            return true;
        ///�������и��ѵ���׶˵���һ����û�У�����false
        if((s != NULL && t == NULL) || (s == NULL && t != NULL))
            return false;
        ///��ǰval��ȣ���������������������ͬ�����£������true���򷵻�true
        if(s->val == t->val && isTheSame(s->left , t->left) && isTheSame(s->right , t->right))
            return true;
        return false;
    }
};

int main() {
    return 0;
}
