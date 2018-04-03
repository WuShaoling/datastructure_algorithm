#include <iostream>
using namespace std;

const int MaxCSTreeSize = 20;
//�����
template<class T>
class CSNode
{
public:
	CSNode();
	CSNode(CSNode<T>* firstchild,CSNode<T>* nextsibling,T newdata);
	CSNode<T>* getFirstChild();
	CSNode<T>* getNextSibling();
	T getData();
	void setFirstChild(T newData);
	void setNextsibling(T newData);
public:
	T data;
	CSNode* firstchild;
	CSNode* nextsibling;
};

template<class T>
CSNode<T>::CSNode()
{
	firstchild = NULL;
	nextsibling = NULL;
}

template<class T>
CSNode<T>::CSNode(CSNode<T>* firstchild,CSNode<T>* nextsibling,T newdata):firstchild(firstchild),nextsibling(nextsibling),data(newdata)
{}

template<class T>
CSNode<T>* CSNode<T>::getFirstChild()
{
	return firstchild;
}

template<class T>
CSNode<T>* CSNode<T>::getNextSibling()
{
	return nextsibling;
}

template<class T>
T CSNode<T>::getData()
{
	return data;
}

template<class T>
void CSNode<T>::setFirstChild(T newData)
{
	firstchild->data = newData;
}

template<class T>
void CSNode<T>::setNextsibling(T newData)
{
	nextsibling->data = newData;
}

//����
template<class T>
class CSTree
{
public:
	CSTree();
	CSTree(const CSTree<T>& csTree);  //�������캯��
	~CSTree();
	const CSTree<T>& operator=(const CSTree<T>& csTree);//���ظ�ֵ�����
	void  createCSTree(); //��������
	void  InitCSTree();   //��ʼ����
	void  destoryCSTree();//������
	bool  isEmptyCSTree();//������Ƿ�Ϊ��
	void  preOrderTraverse();//�������
	void  postOrderTraverse(); //�������
	void  levelOrderTraverse();//�������
	int   heightCSTree();//���߶�
	int   widthCSTree(); //�����
	int   getDegreeCSTree();//���Ķ�--�������н��ȵ����ֵ
	int   nodeCountCSTree();  //��������
	int   LeavesCountCSTree();//��Ҷ�Ӹ���
	int   nodeLevelCSTree(T item);//���item�ڵĲ��
	int   getChildrenCount(const CSNode<T>* p)const;//���ؽ�㺢�Ӹ���
	void  getAllParentCSTree(T item)const;//��item����������
	void  longPathCSNode();//�����ÿ��Ҷ�ӽ�㵽�������·�� ----- δʵ��
	bool  findCSNode(const T item,CSNode<T>*& ret)const; //���ҽ��
	bool  getParentCSTree(const T item,CSNode<T>*& ret)const;//���ҽ��item�ĸ��׽��
	bool  getleftChild(const CSNode<T>* p,CSNode<T>*& ret) const; //��������ߵ��ֵ�
	bool  getrightSibling(const CSNode<T>* p,CSNode<T>*& ret) const; //�������ұߵ��ֵ�
	bool  getAllSibling(const T item) const;//��������ֵ�
	bool  getAllChildren(T item);//������еĺ���
private:
	void create(CSNode<T>*& p);//��pΪ����������
	void  copyTree(CSNode<T>*& copyTreeRoot,CSNode<T>* otherTreeRoot);//����otherTreeRootΪ���ڵ�Ĳ��ֿ�����copyTreeRootΪ���ڵ�Ĳ���
	void  destory(CSNode<T>*& p,int& num);//������pΪ���ڵ�Ĳ���
	void  preOrder(CSNode<T>* p);//���������pΪ���ڵ�Ĳ���
	void  postOrder(CSNode<T>* p);//���������pΪ���ڵ�Ĳ���
	void  levelOrder(CSNode<T>* p);//��α�����pΪ���ڵ�Ĳ���
	int   height(CSNode<T>* p);//������pΪ���ڵ�ĸ߶�
	int   width(CSNode<T>* p);//������pΪ�������Ŀ��
	int   nodeCount(CSNode<T>* p);//������pΪ���ڵ�Ľ�����
	int   leavesCount(CSNode<T>* p);//������pΪ���ڵ��Ҷ�Ӹ���
	void  nodeLevel(T item,CSNode<T>* p,int level,int& nlevel);//������pΪ���ڵ����item���ڲ�Σ����ж��Ԫ�أ���������һ���򷵻أ��������������û�г��֣��򷵻�0
	bool  find(CSNode<T>*p,const T item,bool& isFind,CSNode<T>*& cur)const;//��pָ������У����� ֵΪitem��ָ��
	bool  getParent(CSNode<T>*p,const T item,bool& isFind,bool& isFirst,CSNode<T>*& ret)const;//��pָ�������У���item�ĸ���
	bool getAllParent(T item,CSNode<T>* p,CSNode<T>* path[MaxCSTreeSize],int& seat,bool& isFind)const;//��item���������ȣ�seat��ʾ���һ�����׵��±�
	void  longPath(CSNode<T>* p,int len,int& maxLen,CSNode<T>*& longNode);//�����ÿ��Ҷ�ӽ�㵽�������·��
	int getDegree(CSNode<T>* p);//������Ķȣ����н��ĺ������ֵ��
private:
	CSNode<T>* root;
};

template<class T>
CSTree<T>::CSTree()
{
	root = NULL;
}

template<class T>
CSTree<T>::CSTree(const CSTree<T>& csTree)//�������캯��
{
	if (csTree.root != NULL)
	{
		copyTree(root,csTree.root);
	}
	else
	{
		root = NULL;
	}
}

template<class T>
void  CSTree<T>::copyTree(CSNode<T>*& copyTreeRoot,CSNode<T>* otherTreeRoot)//����otherTreeRootΪ���ڵ�Ĳ��ֿ�����copyTreeRootΪ���ڵ�Ĳ���
{
	if (otherTreeRoot != NULL)
	{
		copyTreeRoot = new CSNode<T>;
		copyTreeRoot->data = otherTreeRoot->data;
		copyTree(copyTreeRoot->firstchild,otherTreeRoot->firstchild);
		copyTree(copyTreeRoot->nextsibling,otherTreeRoot->nextsibling);
	}
}

template<class T>
CSTree<T>::~CSTree() //�������� ע��
{
	if(root != NULL)
	{
		int number = 0;//number��¼���ͷŽ��ĸ�����Ϊ�˵���ʹ��
		destory(root,number);
		InitCSTree();
	}
}

template<class T>
void  CSTree<T>::InitCSTree()   //��ʼ����
{
	root = NULL;
}

template<class T>
void  CSTree<T>::destory(CSNode<T>*& p,int& num)//������pΪ���ڵ�Ĳ���
{
	if (p!=NULL)
	{
		destory(p->firstchild,num);
		destory(p->nextsibling,num);
		delete p;
		num++;
	}
}

template<class T>
void  CSTree<T>::destoryCSTree()//������
{
	int number = 0;
	destory(root,number);
	root = NULL;
	cout<<"������"<<number<<"����㣡"<<endl;
}

template<class T>
const CSTree<T>& CSTree<T>::operator=(const CSTree<T>& csTree)
{
	if (this!=&csTree)//�����Ը�ֵ
	{
		if (root!=NULL)//����ֵ�Ķ��󲻿գ��ͷ�����Դ
		{
			int number = 0;
            destory(root,number);
		}
		if (csTree.root != NULL)
		{
			copyTree(root,csTree.root);
		}
		else
		{
			root = NULL;
		}
	}
	return *this;
}

template<class T>
void  CSTree<T>::createCSTree() //
{
	create(root);
}

template<class T>
void CSTree<T>::create(CSNode<T>*& p)//��pΪ���������� ���ö��У�����������ֻ��ӣ���������
{
   T parent;
   T child;

   //����ѭ������
   CSNode<T> *queue[MaxCSTreeSize];
   int front = 0;
   int rear = 0;

   CSNode<T> *current;
   cout<<"�����븸�׺ͺ��ӣ�"<<endl;
   cin>>parent>>child;
   while(child != '#')//�������
   {
     CSNode<T> *newNode = new CSNode<T>;
	 newNode->data = child;
	 newNode->firstchild = NULL;
	 newNode->nextsibling = NULL;

	 if (parent == '#')//�����
	 {
		 p = newNode;
         queue[(rear++)%MaxCSTreeSize] = p;//�������
	 }
	 else
	 {
         current = queue[front]; //��ȡ�Ӷ�Ԫ��
		 while(current->data != parent)//�ڶ����в��Ҹ��׽��
		 {
			 front = (front+1)%MaxCSTreeSize;
			 current = queue[front];
		 }

		 if (current->data == parent)//�Զ�Ԫ���ǵ�ǰ�½����ĸ���
		 {
             if (current->firstchild == NULL)
             {
				 current->firstchild = newNode;
             }
			 else
			 {
                 current = current->firstchild;
				 while(current->nextsibling!=NULL)
				 {
					 current = current->nextsibling;
				 }
				 current->nextsibling = newNode;
			 }
		 }

		 if ((rear+1)%MaxCSTreeSize != front)//���в����������������
		 {
			 queue[(rear++)%MaxCSTreeSize] = newNode;
		 }
	 }
	 cin>>parent>>child;
   }
}

template<class T>
bool  CSTree<T>::isEmptyCSTree()//������Ƿ�Ϊ��
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void  CSTree<T>::preOrderTraverse()//�������
{
	preOrder(root);
}

template<class T>
void  CSTree<T>::preOrder(CSNode<T>* p)//������������ȼ���cstree���������
{
	if (p!=NULL)
	{
		cout<<p->data<<" ";//cout<<p->getData()<<" ";
		preOrder(p->firstchild);
		preOrder(p->nextsibling);
	}
}

template<class T>
void  CSTree<T>::postOrderTraverse() //�������
{
	postOrder(root);
}

template<class T>
void  CSTree<T>::postOrder(CSNode<T>* p)//���ĺ�������ȼ���cstree���������
{
	if (p!=NULL)
	{
		postOrder(p->firstchild);
		cout<<p->data<<" ";
		postOrder(p->nextsibling);
	}
}

template<class T>
void CSTree<T>::levelOrderTraverse()//�������
{
	levelOrder(root);
}

template<class T>
void CSTree<T>::levelOrder(CSNode<T>* p)//��α�����pΪ���ڵ�Ĳ���
{//�Ͷ������Ĳ������һ��
	//�������
	CSNode<T> *queue[MaxCSTreeSize];
	int front = 0;
	int rear = 0;

	CSNode<T> *current = p;
	queue[(rear++)%MaxCSTreeSize] = p;//�����
	while(rear > front)
	{
		current = queue[(front++)%MaxCSTreeSize];//ȡ���Ӷ�Ԫ��
		cout<<current->data <<" ";
		if (current->firstchild!=NULL)
		{
			for (current=current->firstchild; current!=NULL; current=current->nextsibling)//���ӽ�����
			{
				queue[(rear++)%MaxCSTreeSize] = current;
			}
		}
	}
}

template<class T>
int CSTree<T>::heightCSTree()//���߶�
{
	return height(root);
}

template<class T>
int CSTree<T>::height(CSNode<T>* p)//������pΪ���ڵ�ĸ߶�
{
	int maxHeight = 0;
    if (p==NULL)//����һ
    {
        return 0;
    }

	if (p->firstchild == NULL)//���ڶ�
	{
		return 1;
	}

	int max = 0;//max��¼���ĺ��������߶ȵ����ֵ
	for (CSNode<T>* pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
	{
		int temp = height(pNode);
		if (temp > max)
		{
			max = temp;
		}
	}
	maxHeight = max+1;

	/*for (CSNode<T>* pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
	{
		int temp = height(pNode)+1;
		if (temp > maxHeight)
		{
			maxHeight = temp;
		}
	}*/
	return maxHeight;
}

template<class T>
int CSTree<T>::widthCSTree() //�����
{
	return width(root);
}

template<class T>
int  CSTree<T>::width(CSNode<T>* p)//������pΪ�������Ŀ��
{//����һ�����
	CSNode<T> *queue[MaxCSTreeSize];
	int front = 0;
	int rear = 0;

	CSNode<T> *current;
	int temWidth = 0;
	int maxWidth = 0;
	int last = 0;//��¼ÿ�����һ��Ԫ�ص�λ���±�
	if (p!=NULL)
	{
		queue[rear] = p;//������� rearָ�����һ��Ԫ��
		while(last >= front)
		{
           current = queue[front++];//������
           temWidth++;//��¼������

		   for (current=current->firstchild;current;current=current->nextsibling)//��ǰ������Ԫ�صĺ���ȫ�������
		   {
			   queue[++rear] = current;
		   }

		   if (front > last)//�ϲ���������
		   {
			   last = rear;//����last
			   if (temWidth > maxWidth)
			   {
				   maxWidth = temWidth;//���������
			   }
			   temWidth = 0;
		   }
		}
	}
	return maxWidth;
}

template<class T>
int CSTree<T>::getDegreeCSTree()//���Ķ�--�������н��ȵ����ֵ
{
	return getDegree(root);
}

template<class T>
int CSTree<T>::getDegree(CSNode<T>* p)//������Ķ�
{
	int degree = 0;
	if (p==NULL)
	{
		return 0;
	}
	if (p->firstchild == NULL)
	{
		return 1;
	}
	for (CSNode<T> *pNode=p->firstchild;pNode;pNode=pNode->nextsibling)//����p�Ķ�
	{
        degree++;
	}
	for (CSNode<T> *pNode=p->firstchild;pNode;pNode=pNode->nextsibling)//����p�����к��������Ķ�
	{
		int temDegree = getDegree(pNode);
		if (temDegree > degree)
		{
           degree = temDegree;
		}
	}
    return degree;
}

template<class T>
int CSTree<T>::nodeCountCSTree()  //��������
{
	return nodeCount(root);
}

template<class T>
int   CSTree<T>::nodeCount(CSNode<T>* p)//������pΪ���ڵ�Ľ�����
{
	int count = 0;
	if (p == NULL)
	{
		return 0;
	}
	if (p->firstchild == NULL)
	{
		return 1;
	}
	for (CSNode<T>* pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
	{
        count += nodeCount(pNode);
	}
	return count+1;
}

template<class T>
int CSTree<T>::LeavesCountCSTree()//��Ҷ�Ӹ���
{
	return leavesCount(root);
}

template<class T>
int CSTree<T>::leavesCount(CSNode<T>* p)//������pΪ���ڵ��Ҷ�Ӹ���
{
	int leavecount = 0;
    if (p==NULL)
    {
		return 0;
    }
	if (p->firstchild == NULL)
	{
		return 1;
	}
	for (CSNode<T>* pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
	{
        leavecount += leavesCount(pNode);
	}
	return leavecount;
}

template<class T>
int CSTree<T>::nodeLevelCSTree(T item)//���item�ڵĲ��
{
	int nlevel = 0;
	nodeLevel(item,root,1,nlevel);
	return nlevel;
}

template<class T>
void  CSTree<T>::nodeLevel(T item,CSNode<T>* p,int level,int& nlevel)//������pΪ���ڵ����item���ڲ�Σ����ж��Ԫ�أ���������һ���򷵻أ��������������û�г��֣��򷵻�0
{//level��¼��ǰ�Ѿ��鵽�ڼ���
   if (p==NULL)
   {
	   return;
   }
   //if (nlevel)//nlevel��Ϊ0,��ʾ�Ѿ��ҵ�   �˲���Ҫ�𣿾����鲻��Ҫ
   //{
	  // return;
   //}
   if (p->data == item)
   {
	   nlevel = level;
	   return;
   }
   for (CSNode<T> *pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
   {
	   nodeLevel(item,pNode,level+1,nlevel);
   }
}

template<class T>
int CSTree<T>::getChildrenCount(const CSNode<T>* p)const//���ؽ�㺢�Ӹ���
{
	int count = 0;
	if (p!=NULL)
	{
		if (p->firstchild == NULL)
		{
			return 0;
		}
		else
		{
			for (CSNode<T> *pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
			{
                count++;
			}
		}
	}
	return count;
}

template<class T>
void  CSTree<T>::getAllParentCSTree(T item)const//��item����������
{
	CSNode<T> *path[MaxCSTreeSize];
	int len = 0;
	bool isFind = false;
	getAllParent(item,root,path,len,isFind);
	cout<<item<<"���������ȣ�";
	for (int i=0;i<len;i++)
	{
		cout<<path[i]->data<<" ";
	}
	cout<<endl;
}

/*˼��:
ʹ��һ�����鱣��˫�׽��
˫�׷������飬֮�󵱴��������Լ�����������ʱ�����û�ҵ�����������Ͳ���������˫�׽�㣬ֱ�ӰѸý���Ƴ����顣
*/
template<class T>
bool CSTree<T>::getAllParent(T item,CSNode<T>* p,CSNode<T>* path[MaxCSTreeSize],int& len,bool& isFind)const//��item���������ȣ�seat��ʾ���һ�����׵��±�
{//�úÿ��ǣ���������Ƚ�
     if (isFind)
     {
		 return isFind;
     }
	 if (p==NULL)
	 {
		 return false;
	 }
	 if (p->data == item)
	 {
		 isFind = true;
		 return isFind;
	 }
	 else
	 {
		 path[len++] = p;//û���ҵ��������ʵĽ�����path�����У��д��޳�һЩ���
		 getAllParent(item,p->firstchild,path,len,isFind);
		 if (!isFind)
		 {
			 len = len-1;
			 getAllParent(item,p->nextsibling,path,len,isFind);
		 }
	 }
	 return isFind;
}

template<class T>
void  CSTree<T>::longPathCSNode()//�����ÿ��Ҷ�ӽ�㵽�������·�� ----- δʵ��
{
	int len = 0;
	int maxlen = 0;
	CSNode<T> *longNode;
	longPath(root,len,maxlen,longNode);
}

template<class T>
void  CSTree<T>::longPath(CSNode<T>* p,int len,int& maxLen,CSNode<T>*& longNode)//�����ÿ��Ҷ�ӽ�㵽�������·��
{//˼�룺
  //δʵ��
}

template<class T>
bool  CSTree<T>::findCSNode(const T item,CSNode<T>*& ret)const //���ҽ��
{
	bool isFind = false;
	find(root,item,isFind,ret);
	return isFind;
}

template<class T>
bool  CSTree<T>::find(CSNode<T>*p,const T item,bool& isFind,CSNode<T>*& cur)const//��pָ�������,����ֵΪitem��ָ��
{
	if (isFind)//����һ
	{
		return isFind;
	}
	if (p==NULL)//���ڶ�
	{
		cur = NULL;
		return isFind;
	}
	if (p->data == item)//������
	{
		cur = p;
		isFind = true;
		return isFind;
	}
	else
	{
		for (CSNode<T> *pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
		{
			find(pNode,item,isFind,cur);
			if (isFind)//�ҵ�������
			{
				return isFind;
			}
		}
	}
	return isFind;
}

template<class T>
bool  CSTree<T>::getParentCSTree(const T item,CSNode<T>*& ret)const//���ҽ��item�ĸ��׽��
{
	bool isFind = false;
	bool isFirst = true;
	getParent(root,item,isFind,isFirst,ret);
	return isFind;
}

template<class T>
bool  CSTree<T>::getParent(CSNode<T>*p,const T item,bool& isFind,bool& isFirst,CSNode<T>*& ret)const
{//��Ҫ�ú����
   if (isFind)
   {
	   return isFind;
   }
   if (p==NULL)
   {
	   return false;
   }
   if (p->data == item)
   {
	   if (p == root)
	   {
		   cout<<"��Ԫ���Ǹ���㣬û�и��ף�"<<endl;
		   isFind = false;
		   return isFind;
	   }
	   else
	   {
		   isFind = true;//�˴����ܸ�ret��ֵ��ֻ���ڵݹ��ȥ����ܼ����õ����׵�ָ��
		   return isFind;
	   }
   }
   for (CSNode<T> *pNode=p->firstchild;pNode;pNode=pNode->nextsibling)
   {
	   getParent(pNode,item,isFind,isFirst,ret);
	   if (isFind&&isFirst)
		   //���ݹ�����Ľ��������ҵ�����Ϊret��ֵ����Ϊ�ݹ��ڻ��˵�ʱ��isFind��Ҳ��true��
		   //������isFirst�ͻ���Խ��ret��ֵ����һ·����һ·��ֵ��
		   //���Ҫ�����������������Ҫ�������������ֻ�е�һ�γ�����������ʱ���Ϊ�丳ֵ
	   {
		   isFirst = false;
		   ret = p;
		   return isFind;
	   }

   }
   return isFind;
}

template<class T>
bool  CSTree<T>::getleftChild(const CSNode<T>* p,CSNode<T>*& ret) const   //��������ߵ��ֵ�
{
	if (p==NULL)
	{
		return false;
	}
	else
	{
		if (getParentCSTree(p->data,ret))
		{
			ret = ret->firstchild;
			return true;
		}
		else
		{
			return false;
		}
	}
}

template<class T>
bool  CSTree<T>::getrightSibling(const CSNode<T>* p,CSNode<T>*& ret) const //�������ұߵ��ֵ�
{
	if (p==NULL)
	{
		return false;
	}
	else
	{
		if (getParentCSTree(p->data,ret))
		{
			CSNode<T> *node = ret->firstchild;
			while(node->nextsibling)
			{
				node = node->nextsibling;
			}
			ret = node;
			return true;
		}
		else
		{
			return false;
		}
	}
}

template<class T>
bool  CSTree<T>::getAllSibling(const T item) const //��������ֵ�
{
	bool isFind = false;
	CSNode<T> *ret = NULL;
	isFind = getParentCSTree(item,ret);
	if (!isFind)
	{
		return false;
	}
	else
	{
		isFind = false;
		cout<<item<<"�������ֵܣ�";
		for (CSNode<T> *pNode=ret->firstchild;pNode;pNode=pNode->nextsibling)
		{
			if (pNode->data != item)
			{
				isFind = true;
				cout<<pNode->data<<" ";
			}
		}
		cout<<endl;
		return isFind;
	}

}

template<class T>
bool  CSTree<T>::getAllChildren(T item)//������еĺ���
{
	CSNode<T> *ret = NULL;
	bool isFind = false;
	findCSNode(item,ret);

	cout<<item<<"�����к��ӣ�";
	for(CSNode<T> *pNode=ret->firstchild;pNode;pNode=pNode->nextsibling)
	{
		isFind = true;
        cout<<pNode->data<<" ";
	}
	cout<<endl;

	return isFind;
}

int main()
{
	CSTree<char> tree;
	tree.createCSTree();
	cout<<"�������������";
	tree.preOrderTraverse();
	cout<<endl;
	cout<<"���ĺ��������";
	tree.postOrderTraverse();
	cout<<endl;
    cout<<"���Ĳ��������";
	tree.levelOrderTraverse();
	cout<<endl;
	cout<<"���ĸ߶ȣ�"<<tree.heightCSTree()<<endl;
	cout<<"���Ŀ�ȣ�"<<tree.widthCSTree()<<endl;
    cout<<"���Ľ�������"<<tree.nodeCountCSTree()<<endl;
	cout<<"����Ҷ�ӽ��ĸ�����"<<tree.LeavesCountCSTree()<<endl;
	cout<<"���Ķȣ�"<<tree.getDegreeCSTree()<<endl;
    cout<<"F�����еĲ�����"<<tree.nodeLevelCSTree('F')<<endl;
	tree.getAllParentCSTree('K');
	cout<<endl;
	CSNode<char>* ret;
    if (tree.findCSNode('H',ret))
    {
		cout<<ret->data<<"�ĸ��׽�㣺";
    }
	CSNode<char>* parent;
    tree.getParentCSTree(ret->data,parent);
	cout<<parent->data<<endl;
	return 0;
}
