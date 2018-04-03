#include<iostream>
#include<string>
#include<stack>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> paranStack;
        int maxLength=0;
        int lastValidIndx=0;
        for (int indx=0; indx<s.length(); indx++) {
            if (s[indx]=='(') //���������ţ�ֱ�Ӵ��롣
                paranStack.push(indx);
            else { //���������ţ����������
                if (paranStack.empty()) //�����ʱջ���������Ѿ����������ˣ�û�ж����������������Ե�ǰ���������ˣ���ô��ǰ�������žͱ��������ˣ�������ǰ�Ӵ����Խ����ˣ���ʱ��������Ҳ��Ϊ����һ��group�ķֽ�㣬��ʱ�������±�Ϊindex��������һ��group����ʼ��Ϊindex+1,�൱��skip����ǰ�������š�
                    lastValidIndx=indx+1;
                else { //�����ʱջ���գ����������������1��ջ����ʣ��1�������ź͵�ǰ��������� 2)ջʣ�²�ֹ1�������ţ�
                    paranStack.pop();
                    if (paranStack.empty())  //ջpop()֮ǰ����ʣ��1�������ţ�pop()֮��ջ���ˣ���ʱgroup����Ϊindx-lastValidIndx
                        maxLength=max(maxLength, indx-lastValidIndx+1);
                    else  //ջ��pop()֮ǰʣ�²�ֹ1�������ţ���ʱ��������������ʹ���µ�group�γɡ���()(()())��index=4ʱ��stack����2��������
                        maxLength=max(maxLength, indx-paranStack.top());
                }
            }
        }
        return maxLength;
    }
};

int main() {
    Solution s;
    string str;
    while(cin >> str) {
        cout << s.longestValidParentheses(str) << endl;
    }
    return 0;
}
