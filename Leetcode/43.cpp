#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        //���������һ���������ַ�����ʾΪ�գ��򷵻ؿ��ַ���
        if (num1.empty() || num2.empty())
            return string();

        if (num1 == "0" || num2 == "0")
            return "0";

        //���������ӵ�λ����λ���㣬��ת���������ַ���
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        //�����������ַ����ĳ���
        int len1 = strlen(num1.c_str()), len2 = strlen(num2.c_str());

        //����˷�����ַ���
        string ret = "";
        //�����λ
        int carry = 0;

        for (int i = 0; i < len1; i++) {
            //�����Ĵ�����ʼλ
            size_t pos = i;
            for (int j = 0; j < len2; j++) {
                int temp = (num1[i] - '0') * (num2[j] - '0') + carry;

                //��ǰλ������
                if (pos < ret.length()) {
                    temp = temp + (ret[pos] - '0');
                    ret[pos] = temp % 10 + '0';
                }//if
                else {
                    ret.append(1, temp % 10 + '0');
                }//else
                //������һ����λ
                carry = temp / 10;
                //�����������һλ
                pos++;
            }//for
            if (carry > 0)
                ret.append(1, carry + '0');
            carry = 0;
        }//for

        //��ת��������ַ���
        reverse(ret.begin(), ret.end());
        return ret;

    }
};
int main() {

}
