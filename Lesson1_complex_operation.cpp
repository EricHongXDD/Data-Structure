/*
 * �����ܣ����ʽ���������
 * �汾�ţ�2022-09-15
 * ���뻷����MinGW CLion 2021.2.3(C++17)
*/

#include <iostream>
#include <cmath>

using namespace std;

typedef struct { // ���帴������
    float rpart; // ����ʵ��
    float ipart; // �����鲿
}*PCOMPLEX, COMPLEX;// ����������

void input (PCOMPLEX); // ����
void output (PCOMPLEX); // ���
void add(PCOMPLEX, PCOMPLEX, PCOMPLEX); // �ӷ�
void sub(PCOMPLEX, PCOMPLEX, PCOMPLEX); // ����
void mult(PCOMPLEX, PCOMPLEX, PCOMPLEX); // �˷�
void divi(PCOMPLEX, PCOMPLEX, PCOMPLEX); // ����

int main() {
    PCOMPLEX num = (PCOMPLEX) malloc(sizeof(COMPLEX) * 2);
    PCOMPLEX res = (PCOMPLEX) malloc(sizeof(COMPLEX) * 1);
    input (num);
    input (num+1);
    cout << "��һ������Ϊ"; output (num); cout << endl;
    cout << "�ڶ�������Ϊ"; output (num+1); cout << endl;
    add (num, num+1, res);
    output (num); cout << " + "; output (num+1); cout << " �Ľ��Ϊ "; output (res); cout << endl;
    sub (num, num+1, res);
    output (num); cout << " - "; output (num+1); cout << " �Ľ��Ϊ "; output (res); cout << endl;
    mult (num, num+1, res);
    output (num); cout << " * "; output (num+1); cout << " �Ľ��Ϊ "; output (res); cout << endl;
    divi (num, num+1, res);
    output (num); cout << " / "; output (num+1); cout << " �Ľ��Ϊ "; output (res); cout << endl;
    return 0;
}

void input (PCOMPLEX num){
    cout << "���븴����ʵ�����鲿��" << endl;
    cin >> num->rpart >> num->ipart; // ���븴��
}

void output (PCOMPLEX num){
    char f;
    // �ж�����ķ���
    if (num->ipart > 0){
        f = '+';
    }
    else if (num->ipart < 0){
        f = '-';
    }
    else{ // ��Ϊʵ����������鲿
        cout << "ʵ��" << num->rpart;
        return;
    }
    // ����Ϊʵ����������鲿
    cout << "����" << num->rpart << f << abs(num->ipart) << "i";
}

void add(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    res->rpart = num1->rpart + num2->rpart; // ����ʵ���ĺ�
    res->ipart = num1->ipart + num2->ipart; // �����鲿�ĺ�
}

void sub(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    res->rpart = num1->rpart - num2->rpart; // ����ʵ���Ĳ�
    res->ipart = num1->ipart - num2->ipart; // �����鲿�Ĳ�
}

void mult(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    res->rpart = (num1->rpart * num2->rpart) - (num1->ipart * num2->ipart); // ����ʵ���Ļ�
    res->ipart = (num1->ipart * num2->rpart) + (num1->rpart * num2->ipart); // �����鲿�Ļ�
}

void divi(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    float temp = (pow(num2->rpart, 2) + pow(num2->ipart, 2));
    if (temp!=0)
    {
        res->rpart = (num1->rpart * num2->rpart + num1->ipart * num2->ipart) / temp; // ����ʵ������
        res->ipart = (num1->ipart * num2->rpart - num1->rpart * num2->ipart) / temp; // �����鲿����
    }
    else
    {
        cout << "����Ϊ0" << endl;
        exit(-1); // ����Ϊ0�����Դ������-1��������
    }
}
