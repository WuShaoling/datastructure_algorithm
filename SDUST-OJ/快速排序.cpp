#include<iostream>
using namespace std;
void quickSort(int a[],int,int);
int main()
{
    int array[]= {34,65,12,43,67,5,78,10,3,70},k;
    int len=sizeof(array)/sizeof(int);
    cout<<"The orginal arrayare:"<<endl;
    for(k=0; k<len; k++)
        cout<<array[k]<<",";
    cout<<endl;
    quickSort(array,0,len-1);
    cout<<"The sorted arrayare:"<<endl;
    for(k=0; k<len; k++)
        cout<<array[k]<<",";
    cout<<endl;
    system("pause");
    return 0;
}

void quickSort(int s[], int l, int r)
{
    if (l< r)
    {
        int i = l, j = r, max = s[l];
        while (i < j)
        {
            while(i < j && s[j] < max) // ���������ҵ�һ������x����
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && max < s[i]) // ���������ҵ�һ��С�ڵ���x����
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = max;
        quickSort(s, l, i - 1); // �ݹ����
        quickSort(s, i + 1, r);
    }
}
