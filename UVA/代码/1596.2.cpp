#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<sstream>
#include<cctype>
#include<map>
using namespace std;

class node {
public:
    node(int l = 0) : len(l) {}
    int len;//����
    map<int, int> value;//��ֵ���±�
};

map<string, node> mmap;//�洢����������
bool flag = true;

//������������
string getName(string str) {
    int pos = str.find_first_of('[');
    return str.substr(0, pos);
}

//��ȡ[]�е�����
string getValue(string str) {
    int pos1 = str.find_first_of('[');
    int pos2 = str.find_last_of(']');
    return str.substr(pos1 + 1, pos2 - pos1 - 1);
}

//�ݹ���ֵ
int getNum(string str) {//b[10]
    if(isdigit(str[0])) {
        int pos = 0;
        stringstream ss(str);
        ss >> pos;
        return pos;
    } else {
        string name = getName(str);
        int pos = getNum(getValue(str));
        if(!mmap[name].value.count(pos)){
            flag = false;
            return 0;
        }
        return mmap[name].value[pos];
    }
}

//��ӽڵ�
bool addNode(string str) {//a[b[10]]
    string name = getName(str);
    flag = true;
    int len = getNum(getValue(str));
    if(!flag)
        return false;
    mmap[name] = node(len);
    return true;
}

//����ǰ�벿��
bool dealFront(string str_front, int &pos_f){
    string name = getName(str_front);
    flag = true;
    pos_f = getNum(getValue(str_front));
    if(!flag)
        return false;
    if(mmap[name].len <= pos_f)
        return false;
    return true;
}

bool dealBack(string str_back, int &value_b){//a[a[0]]=  a[ a[0] ]
    flag = true;
    value_b = getNum(str_back);
    if(!flag)
        return false;
    return true;
}

//��ֵ
bool massign(string row) { //a[a[0]]=a[a[0]]
    int equelpos = row.find_first_of('=');
    string str_front = row.substr(0, equelpos);
    string str_back = row.substr(equelpos + 1);
    int pos_f = 0;
    int value_b = 0;
    if(!dealFront(str_front, pos_f)) return false;
    if(!dealBack(str_back, value_b)) return false;
    string name = getName(str_front);
    mmap[name].value[pos_f] = value_b;
    return true;
}

int main() {
    string str;
    while(cin >> str) {
        if(str[0] == '.')
            break;
        mmap.clear();
        vector<string> vv;
        vv.push_back(str);
        string ss;
        while(cin >> ss) {
            if(ss[0] == '.')
                break;
            vv.push_back(ss);
        }
        int pos = 0;
        for(int i = 0; i < vv.size(); i++) {
            string row = vv[i];
            if(row.find_first_of('=') == row.npos) { //��������
                if(!addNode(row)) {
                    pos = i + 1;
                    break;
                }
            } else { //��ֵ
                if(!massign(row)) {
                    pos = i + 1;
                    break;
                }
            }
        }
        cout << pos << endl;
    }
    return 0;
}
