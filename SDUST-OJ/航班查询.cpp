#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 1001000     //���������
#define MAX_SIZE 30     //����ż��ص��������ֵ
#define MAX_PRICE 10000 //��߼�

FILE* fileInput;     //��������
int N; //��������

/*����ṹ��*/
typedef struct{
    char flight_number[MAX_SIZE];   //�����
    char begin_place[MAX_SIZE];     //��d��վ
    char end_place[MAX_SIZE];       //�յ�վ
    char air_date[MAX_SIZE];        //����1-7
    int begin_time;                 //���ʱ���÷�������ʾ
    int end_time;                   //����ʱ���÷�������ʾ
    int price;                      //�۸�
}AirLineNode, *AirLine;

/*����ṹ��*/
typedef struct ListNode{
    AirLine data;
    struct ListNode* next;
}ListNode, *List;

AirLine airline[MAX]; //��������
List L;               //���������������

/*�����ʾ��������ʾ��Ϣ*/
void Show(){
    printf("*******************************************************\n");
    printf("                     �������ϵͳ\n\n");
    printf("�밴��ʾ������Ӧ���ֽ��в��� : \n\n");
    printf("     0���˳�ϵͳ\n");
    printf("     1������ʼվ��ѯ����\n");
    printf("     2�����յ�վ��ѯ����\n");
    printf("     3��������Ų�ѯ����\n");
    printf("     4�������ʱ���ѯ����\n");
    printf("     5��������ʱ���ѯ����\n");
    printf("     6���鿴���к���\n");
    printf("     9�������Ļ\n\n");
    printf("*******************************************************\n");
}

/*ת��ʱ�亯��*/
void getTime(int *time, char t1[]){
    char t2[5];
    int flag = 0;
    for(int x = 0; t1[x] != 0; x++){
        if(x == strlen(t1) - 1){
            t2[flag++] = t1[x];
            t2[flag++] = 0;
            *time += atoi(t2);
        }
        if(t1[x] == ':'){
            t2[flag++] = 0;
            *time = atoi(t2) * 60;
            flag = 0;
        }else
            t2[flag++] = t1[x];
    }
}

/*���뺽�� ���ļ�����*/
void getAirLine(){
    if(fileInput = fopen("D:\\data.txt","r")){
        fscanf(fileInput, "%d", &N);
        for(int i = 0; i < N; i++){
            airline[i] = new AirLineNode;
            char t1[MAX_SIZE];
            char t2[MAX_SIZE];
            fscanf(fileInput, "%s %s %s %s %s %s %d", airline[i]->flight_number, airline[i]->begin_place, airline[i]->end_place, airline[i]->air_date, t1, t2, &airline[i]->price);
            getTime(&(airline[i]->begin_time), t1);
            getTime(&(airline[i]->end_time), t2);
        }
        fclose(fileInput);
    }
}

/*�ź����*/
void SortFlightNumber(){
    List list[26];
    List it[26];
    for(int i = 0; i < 26; i++){
        list[i] = new ListNode;
        list[i]->next = NULL;
        it[i] = list[i];
    }
    for(int i = 0; i < N; i++){
        int x = (airline[i]->flight_number)[5] - '0';
        it[x]->next = new ListNode;
        it[x]->next->data = airline[i];
        it[x]->next->next = NULL;
        it[x] = it[x]->next;
    }
    int flag = 0, rec = 0;
    for(int i = 0; i < 26; i++){
        if(list[i]->next != NULL){
            if(flag == 0){
                L = list[i];
                flag = 1;
                rec = i;
            }else{
                it[rec]->next = list[i]->next;
                rec = i;
            }
        }
    }
    for(int aa = 4; aa >= 2; aa--){
        List tt = L->next;
        for(int i = 0; i < 10; i++){
            list[i]->next = NULL;
            it[i] = list[i];
        }
        while(tt){
            int x = (tt->data->flight_number)[aa] - '0';
            it[x]->next = tt;
            it[x] = it[x]->next;
            tt = tt->next;
        }
        for(int i = 0; i < 10; i++)
            it[i]->next = NULL;
        flag = 0;
        rec = 0;
        for(int i = 0; i < 10; i++){
            if(list[i]->next != NULL){
                if(flag == 0){
                    L = list[i];
                    flag = 1;
                    rec = i;
                }else{
                    it[rec]->next = list[i]->next;
                    rec = i;
                }
            }
        }
    }
    int re = 0;
    for(int xx = 1; xx >= 0; xx--){
        List tt = L->next;
        for(int i = 0; i < 26; i++){
            list[i]->next = NULL;
            it[i] = list[i];
        }
        while(tt){
            int x = (tt->data->flight_number)[xx] - 'A';
            it[x]->next = tt;
            it[x] = it[x]->next;
            tt = tt->next;
        }
        for(int i = 0; i < 26; i++)
            it[i]->next = NULL;
        flag = 0;
        rec = 0;
        for(int i = 0; i < 26; i++){
            if(list[i]->next != NULL){
                if(flag == 0){
                    L = list[i];
                    re = i;
                    flag = 1;
                    rec = i;
                }else{
                    it[rec]->next = list[i]->next;
                    rec = i;
                }
            }
        }
    }
    for(int i = 0; i < 26; i++){
        if(re != i)
            delete list[i];
    }
}

/*�۸�����*/
void SortPrice(){
    List list[MAX_PRICE];
    List it[MAX_PRICE];
    List tt = L->next;
    for(int i = 0; i < MAX_PRICE; i++){
        list[i] = new ListNode;
        list[i]->next = NULL;
        it[i] = list[i];
    }
    while(tt){
        int x = tt->data->price;
        it[x]->next = tt;
        it[x] = it[x]->next;
        tt = tt->next;
    }
    for(int i = 0; i < MAX_PRICE; i++)
        it[i]->next = NULL;
    int flag = 0;
    int rec = 0;
    for(int i = 0; i < MAX_PRICE; i++){
        if(list[i]->next != NULL){
            if(flag == 0){
                List ttt = L;
                L = list[i];
                delete ttt;
                flag = 1;
                rec = i;
                continue;
            }else{
                it[rec]->next = list[i]->next;
                rec = i;
            }
        }
        delete list[i];
    }
}

/*���ʱ������*/
void SortBeginTime(){
    List list[1450];
    List it[1450];
    List tt = L->next;
    for(int i = 0; i < 1450; i++){
        list[i] = new ListNode;
        list[i]->next = NULL;
        it[i] = list[i];
    }
    while(tt){
        int x = tt->data->begin_time;
        it[x]->next = tt;
        it[x] = it[x]->next;
        tt = tt->next;
    }
    for(int i = 0; i < 1450; i++)
        it[i]->next = NULL;
    int flag = 0;
    int rec = 0;
    for(int i = 0; i < 1450; i++){
        if(list[i]->next != NULL){
            if(flag == 0){
                List ttt = L;
                L = list[i];
                delete ttt;
                flag = 1;
                rec = i;
                continue;
            }else{
                it[rec]->next = list[i]->next;
                rec = i;
            }
        }
        delete list[i];
    }
}

/*�Ժ����������*/
void RadixSort(){
    SortFlightNumber();  //���ź����
    SortPrice();         //�������ͬ�Լ۸�����
    SortBeginTime();     //�����ʱ������
    int ff = 0;
    List p = L->next;
    while(p){
        airline[ff++] = p->data;
        List t = p;
        p = p->next;
        delete t;
    }
}

/*��ʼվ����  ˳�����*/
void Search_Original(){
    char data[MAX_SIZE];
    printf("��������ʼվ : \n");
    scanf("%s", data);
    printf("�����   ���վ     �յ�վ     ����        ���ʱ��  ����ʱ��  �۸�\n");
    bool have = false;
    for(int j = 0; j < N; j++){
        if(strcmp(airline[j]->begin_place, data) == 0){
            int hour1 = (airline[j]->begin_time) / 60;
            int minu1 = (airline[j]->begin_time) % 60;
            int hour2 = (airline[j]->end_time) / 60;
            int minu2 = (airline[j]->end_time) % 60;
            printf("%-8s %-10s %-10s %-10s  %02d:%02d     %02d:%02d     %d\n", airline[j]->flight_number, airline[j]->begin_place, airline[j]->end_place, airline[j]->air_date, hour1, minu1, hour2, minu2, airline[j]->price);
            have = true;
        }
    }
    if(!have)
        printf("NO SUCH FLIGHT\n");
}

/*�յ�վ���� ˳�����*/
void Search_Terminal(){
    char data[MAX_SIZE];
    printf("�����뵽��վ :\n");
    scanf("%s", data);
    printf("�����   ���վ     �յ�վ     ����        ���ʱ��  ����ʱ��  �۸�\n");
    bool have = false;
    for(int j = 0; j < N; j++){
        if(strcmp(airline[j]->end_place, data) == 0){
            int hour1 = (airline[j]->begin_time) / 60;
            int minu1 = (airline[j]->begin_time) % 60;
            int hour2 = (airline[j]->end_time) / 60;
            int minu2 = (airline[j]->end_time) % 60;
            printf("%-8s %-10s %-10s %-10s  %02d:%02d     %02d:%02d     %d\n", airline[j]->flight_number, airline[j]->begin_place, airline[j]->end_place, airline[j]->air_date, hour1, minu1, hour2, minu2, airline[j]->price);
            have = true;
        }
    }
    if(!have)
        printf("NO SUCH FLIGHT\n");
}

/*��������� ˳�����*/
void Search_Flight_Number(){
    char data[MAX_SIZE];
    printf("�����뺽��� :\n");
    scanf("%s", data);
    printf("�����   ���վ     �յ�վ     ����        ���ʱ��  ����ʱ��  �۸�\n");
    bool have = false;
    for(int j = 0; j < N; j++){
        if(strcmp(airline[j]->flight_number, data) == 0){
            int hour1 = (airline[j]->begin_time) / 60;
            int minu1 = (airline[j]->begin_time) % 60;
            int hour2 = (airline[j]->end_time) / 60;
            int minu2 = (airline[j]->end_time) % 60;
            printf("%-8s %-10s %-10s %-10s  %02d:%02d     %02d:%02d     %d\n", airline[j]->flight_number, airline[j]->begin_place, airline[j]->end_place, airline[j]->air_date, hour1, minu1, hour2, minu2, airline[j]->price);
            have = true;
            break;
        }
    }
    if(!have)
        printf("NO SUCH FLIGHT\n");
}

/*ʱ������ ���ַ�*/
void Search_Begin_Tiem(int cmd){
    char data[MAX_SIZE];
    int begin_time = 0;
    int end_time = 0;
    printf("������ʱ��� :\n");
    scanf("%s", data);
    printf("�����   ���վ     �յ�վ     ����        ���ʱ��  ����ʱ��  �۸�\n");
    getTime(&begin_time, data);
    if(begin_time >= 1440)
        begin_time = 0;
    scanf("%s", data);
    getTime(&end_time, data);
    if(end_time >= 1440)
        end_time = 0;
    if(cmd == 4){
        int low = 0;
        int high = N - 1;
        int mid = 0;
        bool have = false;
        while(low <= high){
            mid = (low + high) / 2;
            if(airline[mid]->begin_time >= begin_time && airline[mid]->begin_time <= end_time){
                have = true;
                break;
            }
            else if(airline[mid]->begin_time > end_time)
                high = mid - 1;
            else if(airline[mid]->begin_time < begin_time)
                low = mid + 1;
        }
        if(have){
            while(mid--){
                if(airline[mid]->begin_time <= begin_time)
                    break;
            }
            if(airline[mid]->begin_time < begin_time)
                mid++;
            for(int j = mid; j < N; j++){
                if(airline[j]->begin_time > end_time)
                    break;
                int hour1 = (airline[j]->begin_time) / 60;
                int minu1 = (airline[j]->begin_time) % 60;
                int hour2 = (airline[j]->end_time) / 60;
                int minu2 = (airline[j]->end_time) % 60;
                printf("%-8s %-10s %-10s %-10s  %02d:%02d     %02d:%02d     %d\n", airline[j]->flight_number, airline[j]->begin_place, airline[j]->end_place, airline[j]->air_date, hour1, minu1, hour2, minu2, airline[j]->price);
            }
        }else
            printf("NO SUCH FLIGHT\n");
    }
    else{
        int low = 0;
        int high = N - 1;
        int mid = 0;
        bool have = false;
        while(low <= high){
            mid = (low + high) / 2;
            if(airline[mid]->end_time >= begin_time && airline[mid]->end_time <= end_time){
                have = true;
                break;
            }
            else if(airline[mid]->end_time > end_time)
                high = mid - 1;
            else if(airline[mid]->end_time < begin_time)
                low = mid + 1;
        }
        if(have){
            while(mid--){
                if(airline[mid]->end_time <= begin_time)
                    break;
            }
            if(airline[mid]->end_time < begin_time)
                mid++;
            for(int j = mid; j < N; j++){
                if(airline[j]->end_time > end_time)
                    break;
                int hour1 = (airline[j]->begin_time) / 60;
                int minu1 = (airline[j]->begin_time) % 60;
                int hour2 = (airline[j]->end_time) / 60;
                int minu2 = (airline[j]->end_time) % 60;
                printf("%-8s %-10s %-10s %-10s  %02d:%02d     %02d:%02d     %d\n", airline[j]->flight_number, airline[j]->begin_place, airline[j]->end_place, airline[j]->air_date, hour1, minu1, hour2, minu2, airline[j]->price);
            }
        }else
            printf("NO SUCH FLIGHT\n");
    }
}

/*��ʾ���к���*/
void ShowAllLine(){
    printf("�����   ���վ     �յ�վ     ����        ���ʱ��  ����ʱ��  �۸�\n");
    for(int j = 0; j < N; j++){
        int hour1 = (airline[j]->begin_time) / 60;
        int minu1 = (airline[j]->begin_time) % 60;
        int hour2 = (airline[j]->end_time) / 60;
        int minu2 = (airline[j]->end_time) % 60;
        printf("%-8s %-10s %-10s %-10s  %02d:%02d     %02d:%02d     %d\n", airline[j]->flight_number, airline[j]->begin_place, airline[j]->end_place, airline[j]->air_date, hour1, minu1, hour2, minu2, airline[j]->price);
    }
}

/*����*/
void Search_(int cmd){
    if(cmd == 1) //��ʼվ
        Search_Original();
    if(cmd == 2) //�յ�վ
        Search_Terminal();
    if(cmd == 3)//�������
        Search_Flight_Number();
    if(cmd == 4 || cmd == 5)//��ʱ��
        Search_Begin_Tiem(cmd);
    if(cmd == 6)//��ʾ���к���
        ShowAllLine();
    if(cmd == 9){ //�����Ļ
        system("CLS");
        Show();
    }
}

/*����*/
int Operator(){
    int oper;
    while(1){
        scanf("%d", &oper);
        if(oper == 0){
            printf("Bye-Bye!!\n");
            return 0;
        }
        else
            Search_(oper);
    }
}

/*������*/
int main(){
    Show();       //��ʾ��������ʾ��Ϣ
    getAirLine(); //��ú�����Ϣ
    RadixSort();  //����
    Operator();   //����
}

