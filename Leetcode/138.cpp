#include<iostream>
using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL) return NULL;

        ///���裺l1����ԭ�����еĽڵ㣻l2�����������еĽڵ�
        RandomListNode *new_head, *l1, *l2;

        ///��һ������ÿһ��l1���洴��һ��l2������l1ָ��l2��l2ָ����һ��l1��
        for (l1 = head; l1 != NULL; l1 = l1->next->next) {
            l2 = new RandomListNode(l1->label);
            l2->next = l1->next;
            l2->random = l1->random;
            l1->next = l2;
        }

        ///�ڶ�������l2��random��ֵ��l1��random��nextָ��ľ���l2��random��Ŀ�ꣻ
        new_head = head->next;
        for (l1 = head; l1 != NULL; l1 = l1->next->next) {
            if (l1->random != NULL) l1->next->random = l1->random->next;
        }

        ///����������Ҫ��������������������������������l1
        ///��nextָ�����ĺ���;l2��nextҲָ�����ĺ��档
        for (l1 = head; l1 != NULL; l1 = l1->next) {
            l2 = l1->next;
            l1->next = l2->next;
            if (l2->next != NULL)
                l2->next = l2->next->next;
        }
        return new_head;
    }
};

int main() {
    return 0;
}
