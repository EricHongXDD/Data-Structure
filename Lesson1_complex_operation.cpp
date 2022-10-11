/*
 * 功　能：表达式中括号配对
 * 版本号：2022-09-15
 * 编译环境：MinGW CLion 2021.2.3(C++17)
*/

#include <iostream>
#include <cmath>

using namespace std;

typedef struct { // 定义复数类型
    float rpart; // 复数实部
    float ipart; // 复数虚部
}*PCOMPLEX, COMPLEX;// 复数类型名

void input (PCOMPLEX); // 输入
void output (PCOMPLEX); // 输出
void add(PCOMPLEX, PCOMPLEX, PCOMPLEX); // 加法
void sub(PCOMPLEX, PCOMPLEX, PCOMPLEX); // 减法
void mult(PCOMPLEX, PCOMPLEX, PCOMPLEX); // 乘法
void divi(PCOMPLEX, PCOMPLEX, PCOMPLEX); // 除法

int main() {
    PCOMPLEX num = (PCOMPLEX) malloc(sizeof(COMPLEX) * 2);
    PCOMPLEX res = (PCOMPLEX) malloc(sizeof(COMPLEX) * 1);
    input (num);
    input (num+1);
    cout << "第一次输入为"; output (num); cout << endl;
    cout << "第二次输入为"; output (num+1); cout << endl;
    add (num, num+1, res);
    output (num); cout << " + "; output (num+1); cout << " 的结果为 "; output (res); cout << endl;
    sub (num, num+1, res);
    output (num); cout << " - "; output (num+1); cout << " 的结果为 "; output (res); cout << endl;
    mult (num, num+1, res);
    output (num); cout << " * "; output (num+1); cout << " 的结果为 "; output (res); cout << endl;
    divi (num, num+1, res);
    output (num); cout << " / "; output (num+1); cout << " 的结果为 "; output (res); cout << endl;
    return 0;
}

void input (PCOMPLEX num){
    cout << "输入复数的实部、虚部：" << endl;
    cin >> num->rpart >> num->ipart; // 输入复数
}

void output (PCOMPLEX num){
    char f;
    // 判断输出的符号
    if (num->ipart > 0){
        f = '+';
    }
    else if (num->ipart < 0){
        f = '-';
    }
    else{ // 若为实数，则不输出虚部
        cout << "实数" << num->rpart;
        return;
    }
    // 若不为实数，则输出虚部
    cout << "虚数" << num->rpart << f << abs(num->ipart) << "i";
}

void add(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    res->rpart = num1->rpart + num2->rpart; // 计算实部的和
    res->ipart = num1->ipart + num2->ipart; // 计算虚部的和
}

void sub(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    res->rpart = num1->rpart - num2->rpart; // 计算实部的差
    res->ipart = num1->ipart - num2->ipart; // 计算虚部的差
}

void mult(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    res->rpart = (num1->rpart * num2->rpart) - (num1->ipart * num2->ipart); // 计算实部的积
    res->ipart = (num1->ipart * num2->rpart) + (num1->rpart * num2->ipart); // 计算虚部的积
}

void divi(PCOMPLEX num1, PCOMPLEX num2, PCOMPLEX res){
    float temp = (pow(num2->rpart, 2) + pow(num2->ipart, 2));
    if (temp!=0)
    {
        res->rpart = (num1->rpart * num2->rpart + num1->ipart * num2->ipart) / temp; // 计算实部的商
        res->ipart = (num1->ipart * num2->rpart - num1->rpart * num2->ipart) / temp; // 计算虚部的商
    }
    else
    {
        cout << "除数为0" << endl;
        exit(-1); // 除数为0，则以错误代码-1结束进程
    }
}
