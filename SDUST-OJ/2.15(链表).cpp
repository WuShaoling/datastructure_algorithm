#include<iostream>
#include<string>
using namespace std;
int length = 0;
typedef struct LNode {
	int data; //����������
	struct LNode *next; //����ָ����
} LNode, *List; //LinkListΪָ��ṹ��LNode��ָ������

void ListInsert(List &L, int e) //��e���뵽List��
{
    if(L == NULL){
        List node = new LNode;
        node->data = e;
        L = node;
        node->next = L;
    }else{
        List p = L;
        while(p->next != L){
            p = p->next;
        }
        LNode* node = new LNode;
        node->data = e;
        node->next = L;
        p->next = node;
    }
	length++;
}

void ListOutput(List L) //���List
{
	List p = L;
	while (p->next != L) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << p->data;
	cout << endl;
}

int main() {
	int N;
    cin >> N;
    while(N--){
        List li = NULL;
        int begin;
        int n;
        cin >> n;
        while(n--){
            int t;
            cin >> t;
            ListInsert(li,t);
        }
        ListOutput(li);
//        begin = li->data;
//        List p = li->next;
//        while(length > 1){
//            for(int i = 0; i < begin  - 1; i++){
//                p = p->next;
//                if(p == li)
//                    p = p->next;
//            }
//
//            begin = (p->next)->data;
//            cout << begin << ",";
//            if(p == li)
//                p = p->next;
//            if()
//            List t = p->next;
//
//            p->next = t->next;
//            delete t;
//            length--;
//
//
//        }
    }
}
