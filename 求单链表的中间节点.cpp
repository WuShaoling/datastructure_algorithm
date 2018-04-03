#include<iostream>
using namespace std;

typedef struct ListNode {
    int value;
    ListNode* next;
    ListNode(int v):value(v), next(NULL) {
    }
} *List;

ListNode* getMiddleNode(List head) {
    if(NULL == head)
        return NULL;
    List p_fast = head, p_slow = head;
    ///���p_fast = head->next�����ڵ����Ϊż��ʱ���򷵻ؽ�ǰ���Ǹ��м�ڵ�
    while(p_fast && p_fast->next) {
        p_fast = p_fast->next->next;
        p_slow = p_slow->next;
    }
    return p_slow;
}

int main() {
    int n = 8;
    List h = new ListNode(1);
    List p = h;
    for(int i=2; i<=n; i++) {
        p->next = new ListNode(i);
        p = p->next;
    }
    p = getMiddleNode(h);
    if(p)
        cout << p->value << endl;
    else
        cout << "NULL" << endl;
    return 0;
}
