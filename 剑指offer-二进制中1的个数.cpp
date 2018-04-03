#include<stdio.h>

//a���Ƶķ�ʽ ��������븺������0x80000000�����ջ���0xFFFFFFFF��������ѭ�� 
int numOf1(int a){
	int count = 0;
	while(a){
		if(a & 1)
			count++;
		a = a >> 1;
	} 
	return count;
}

//��ʽ2����i����������a�Ƚϣ����a��32λ����Ҫ�Ƚ�32�� 
int numOf1_2(int a){
	unsigned int i = 1;
	int count = 0;
	while(i){
		if(a & i)
			count++;
		i = i << 1;
	}
	return count;
} 

//��ʽ3����һ��������ȥ1���ٺ�ԭ���������룬��Ѹ���������һ��1���0.
//��ôһ�������Ķ����Ʊ�ʾ���ж��ٸ�1���Ϳ��Խ��ж��ٴ����������� 
int numOf1_3(int a){
	int count = 0;
	while(a){
		++count;
		a = (a - 1) & a;
	}
	return count;
} 

int main(){
	int a;
	scanf("%d", &a);
	int result = numOf1_3(a);	
	printf("%d\n", result);
}
