#include<iostream>
using namespace std;
int code[8][1<<8];
int readchar() //���ж�ȡ���봮
{
    while(1)
    {
        int ch=getchar();
        if(ch!='\r'&&ch!='\n')
            return ch;
    }
}
int readint(int len) //��ȡ���봮��ת��Ϊʮ��������
{
    int v=0;
    while(len--)
        v=v*2+readchar()-'0';
    return v;
}
int readcode() //��ȡ����ͷ����Ӧ��code����
{
    memset(code,0,sizeof(code));
    code[1][0]=readchar();
    for(int len=2; len<=7; len++)
        for(int i=0; i<(1<<len)-1; i++) //����ÿλ��Ϊ1��(1<<len)-1��ע������λ�á�
        {
            int ch=getchar();
            if(ch==EOF)    return 0;
            if(ch=='\n'||ch=='\r')    return 1;
            code[len][i]=ch;
        }
    return 1;//����EOF����0���������룬���򷵻�1����������롣
}
int main()
{
    while(readcode())
    {
        while(1)
        {
            int len=readint(3);
            if(len==0)    break;
            while(1)
            {
                int v=readint(len);
                if(v==(1<<len)-1)    break;
                putchar(code[len][v]);
            }
        }
        putchar('\n');
    }
    return 0;
}
