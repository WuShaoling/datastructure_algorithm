#include<cstdio>
#include<cstring>
using namespace std;

unsigned long long d[100+7];

int main() {
    int n;
    scanf("%d",&n);
    memset(d,0,sizeof(d));
    d[0] = 1;
    for(int i=1; i<=n; i++) ///iö��ÿһ������
        for(int j=0; j<=n; j++) /// ö��ÿһ��Ŀ������nΪ���ս��
            if(j - i >= 0)
                d[j] = d[j] + d[j-i];
    printf("%llu\n",d[n]);
    return 0;
}
