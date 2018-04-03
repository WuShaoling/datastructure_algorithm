#include<iostream>
#include<cstdio>
using namespace std;
typedef int ElemType;
struct LNode
{
    ElemType data;
    struct LNode *next;
};
typedef struct LNode *LinkList; /* ��һ�ֶ���LinkList�ķ��� */

int InitList_CL(LinkList L)
{
    L=(LinkList)malloc(sizeof(struct LNode));
    if(!L) /* �洢����ʧ�� */
        exit(-1);
    (L)->next=L; /* ָ����ָ��ͷ��� */
    return 1;
}
int ClearList_CL(LinkList *L) /* �ı�L */
{
    /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
    LinkList p,q;
    *L=(*L)->next; /* Lָ��ͷ��� */
    p=(*L)->next; /* pָ���һ����� */
    while(p!=*L) /* û����β */
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=*L; /* ͷ���ָ����ָ������ */
    return 1;
}
int ListEmpty_CL(LinkList L)
{
    if(L->next==L) /* �� */
        return true;
    else
        return false;
}
int ListLength_CL(LinkList L)
{
    int i=0;
    LinkList p=L->next; /* pָ��ͷ��� */
    while(p!=L) /* û����β */
    {
        i++;
        p=p->next;
    }
    return i;
}
int GetElem_CL(LinkList L,int i,ElemType *e)
{
    /* ����i��Ԫ�ش���ʱ,��ֵ����e������1,���򷵻�-1 */
    int j=1; /* ��ʼ��,jΪ������ */
    LinkList p=L->next->next; /* pָ���һ����� */
    if(i<=0||i>ListLength_CL(L)) /* ��i��Ԫ�ز����� */
        return -1;
    while(j<i)
    {
        /* ˳ָ��������,ֱ��pָ���i��Ԫ�� */
        p=p->next;
        j++;
    }
    *e=p->data; /* ȡ��i��Ԫ�� */
    return 1;
}
int LocateElem_CL(LinkList L,ElemType e,int(*compare)(ElemType,ElemType))
{
    /* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж����� */
    /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
    /*      ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
    int i=0;
    LinkList p=L->next->next; /* pָ���һ����� */
    while(p!=L->next)
    {
        i++;
        if(compare(p->data,e)) /* �����ϵ */
            return i;
        p=p->next;
    }
    return 0;
}
int PriorElem_CL(LinkList L,ElemType cur_e,ElemType *pre_e)
{
    /* ��ʼ���������Ա�L�Ѵ��� */
    /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
    /*      �������ʧ�ܣ�pre_e�޶��� */
    LinkList q,p=L->next->next; /* pָ���һ����� */
    q=p->next;
    while(q!=L->next) /* pû����β */
    {
        if(q->data==cur_e)
        {
            *pre_e=p->data;
            return true;
        }
        p=q;
        q=q->next;
    }
    return false;
}
int NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e)
{
    /* ��ʼ���������Ա�L�Ѵ��� */
    /* �����������cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣� */
    /*      �������ʧ�ܣ�next_e�޶��� */
    LinkList p=L->next->next; /* pָ���һ����� */
    while(p!=L) /* pû����β */
    {
        if(p->data==cur_e)
        {
            *next_e=p->next->data;
            return true;
        }
        p=p->next;
    }
    return false;
}
int ListInsert_CL(LinkList *L,int i,ElemType e) /* �ı�L */
{
    /* ��L�ĵ�i��λ��֮ǰ����Ԫ��e */
    LinkList p=(*L)->next,s; /* pָ��ͷ��� */
    int j=0;
    if(i<=0||i>ListLength_CL(*L)+1) /* �޷��ڵ�i��Ԫ��֮ǰ���� */
        return -1;
    while(j<i-1) /* Ѱ�ҵ�i-1����� */
    {
        p=p->next;
        j++;
    }
    s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
    s->data=e; /* ����L�� */
    s->next=p->next;
    p->next=s;
    if(p==*L) /* �ı�β��� */
        *L=s;
    return 1;
}
int ListDelete_CL(LinkList *L,int i,ElemType *e) /* �ı�L */
{
    /* ɾ��L�ĵ�i��Ԫ��,����e������ֵ */
    LinkList p=(*L)->next,q; /* pָ��ͷ��� */
    int j=0;
    if(i<=0||i>ListLength_CL(*L)) /* ��i��Ԫ�ز����� */
        return -1;
    while(j<i-1) /* Ѱ�ҵ�i-1����� */
    {
        p=p->next;
        j++;
    }
    q=p->next; /* qָ���ɾ����� */
    p->next=q->next;
    *e=q->data;
    if(*L==q) /* ɾ�����Ǳ�βԪ�� */
        *L=p;
    free(q); /* �ͷŴ�ɾ����� */
    return 1;
}

void visit(ElemType c)
{
    printf("%d ",c);
}
int main()
{
    LinkList L;
    InitList_CL(L);
    ListInsert_CL()
}
