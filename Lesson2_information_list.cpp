/*
 * 功　能：表达式中括号配对
 * 版本号：2022-09-29
 * 编译环境：MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

typedef struct node{
    char name[8]; //姓名
    char sex[3]; // 性别
    int age; //年龄
    char phoneno[12]; // 电话号
    char wechatno[16]; // 微信号
    struct node *pNext; // 指针域
}NODE,*PNODE; // 链表类型名

PNODE create_list(void); // 生成一个链表
int len_list(PNODE); // 求一个链表的长度（头结点）
void empt_list(PNODE); // 清空一个链表（头结点）
void destroy_list(PNODE*); // 销毁一个链表（头结点地址）注意要取地址
PNODE find_pTail(PNODE); // 查找链表的尾结点（头节点）
bool add_list(PNODE, int); // 在链表后增加n个节点（头节点, 个数）
bool insert_list(PNODE, int); // 向链表中某个节点前插入一个节点（头节点, 位置, 值）
void traverse_list(PNODE); // 遍历链表（头节点）
bool delete_list(PNODE, int); // 删除第n个节点，首节点记为第1个节点（头结点，位置）
bool modify_list(PNODE, int); // 修改第n个节点，首节点记为第1个节点（头结点，位置）
PNODE lookup_list(PNODE, string); // 查找含有“xxx”信息的节点位置（头结点，信息）


int main()
{
    PNODE pHead = create_list();
    int len; cout << "输入要通讯录中数据的个数" << endl; cin >> len;
    add_list(pHead, len);
    traverse_list(pHead);
    insert_list(pHead,2); traverse_list(pHead);
    delete_list(pHead,3);traverse_list(pHead);
    modify_list (pHead, 2);traverse_list(pHead);
    PNODE l = lookup_list(pHead, "洪");
    empt_list(pHead); traverse_list(pHead);
    destroy_list(&pHead); traverse_list(pHead);
    return 0;
}

PNODE create_list(void)
{
    PNODE pHead = (PNODE) malloc(sizeof(NODE));
    if (pHead == NULL){
        cout << "动态内存分配失败！" << endl;
        exit(-1);
    }
    pHead->pNext = NULL;
    return pHead;
} // 生成一个通讯录链表并返回其头结点

PNODE find_pTail(PNODE pHead)
{
    PNODE pTail = pHead;
    while (pTail->pNext != NULL)
    {
        pTail = pTail->pNext;
    }
    return pTail;
} // 寻找pHead所指向的链表的尾结点并返回其地址

bool add_list(PNODE pHead, int val)
{
    PNODE pTail = find_pTail(pHead);
    for (int i = 0; i < val; ++i) {
        cout << "输入要加入的第 " << (i+1) << " 条数据" << endl;
        PNODE pNew = (PNODE) malloc(sizeof(NODE));
        pNew->pNext = NULL;
        cout << "姓名："; cin >> pNew->name;
        cout << "性别："; cin >> pNew->sex;
        cout << "年龄："; cin >> pNew->age;
        cout << "手机号："; cin >> pNew->phoneno;
        cout << "微信号："; cin >> pNew->wechatno;
        pTail->pNext = pNew;
        pTail = pNew; // 让pTail始终指向最后一个节点
        cout << "------------------------" << endl;
    }
    return true;
} // 在pHead所指向的链表后面添加上val个节点

bool insert_list(PNODE pHead, int pos)
{
    PNODE p = pHead;
    int i = 0;
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (pNew == NULL){
        cout << "动态内存分配失败！" << endl;
        exit(-1);
    }
    for (; i < pos - 1; ++i) {
        p = p->pNext;
    }
    cout << "输入要插入第" << pos << "个节点前面的数据" << endl;
    cout << "姓名："; cin >> pNew->name;
    cout << "性别："; cin >> pNew->sex;
    cout << "年龄："; cin >> pNew->age;
    cout << "手机号："; cin >> pNew->phoneno;
    cout << "微信号："; cin >> pNew->wechatno;
    pNew->pNext = p->pNext;
    p->pNext = pNew;
    cout << "节点插入成功" << endl;
    cout << "------------------------" << endl;
    return true;
} // 在pHead所指向链表的第pos个节点的前面插入一个新的节点，并且pos的值从1开始

void traverse_list(PNODE pHead)
{
    PNODE p = pHead;
    if (p == NULL){
        cout << "链表不存在或已销毁" << endl;
        cout << "------------------------" << endl;
        return;
    }
    if (p->pNext == NULL){
        cout << "链表为空" << endl;
        cout << "------------------------" << endl;
    }
    else{
        for (int i = 0; p->pNext != NULL; i++){
            p = p->pNext;
            cout << "链表的第 " << (i+1) << " 条数据为：" << endl;
            cout << "姓名:" << p->name << " ";
            cout << "性别:" << p->sex << " ";
            cout << "年龄:" << p->age << " ";
            cout << "手机号:" << p->phoneno << " ";
            cout << "微信号:" << p->wechatno << endl;
            cout << "------------------------" << endl;
        }
    }
} // 遍历头节点为pHead的链表

int len_list(PNODE pHead)
{
    int i = 0;
    for (PNODE p = pHead; p->pNext != NULL; p = p->pNext) {
        i++;
    }
    return i;
} // 求一个链表的长度


void empt_list(PNODE pHead)
{
    PNODE p = pHead;
    PNODE q = p->pNext;
    int len = len_list(pHead);
    for (int i = 0; i < len; ++i) {
        q = p->pNext;
        p->pNext = p->pNext->pNext;
        free (q);
    }
    q = NULL; // 释放了q的内存空间，但是指针q还是存在，所以要让q=NULL，避免野指针
} // 清空链表

void destroy_list(PNODE *pHead)
{
    empt_list(*pHead);
    *pHead = NULL;
} // 销毁一个链表

bool delete_list(PNODE pHead, int pos)
{
    PNODE p = pHead;
    for (int i = 1; i < pos; ++i) {
        p = p->pNext;
    } // p 为删除的前一个节点
    PNODE q = p->pNext;
    free(q);
    q = NULL;
    p->pNext = p->pNext->pNext;
    cout << "已删除第" << pos << "个节点" << endl;
    cout << "------------------------" << endl;
    return true;
} // 删除第pos个节点，首节点记为第1个节点

bool modify_list(PNODE pHead, int pos){
    PNODE p = pHead;
    for (int i = 0; i < pos; ++i) {
        p = p->pNext;
    } // p 为修改的节点
    cout << "输入要修改的第" << pos << "个节点的数据" << endl;
    cout << "姓名："; cin >> p->name;
    cout << "性别："; cin >> p->sex;
    cout << "年龄："; cin >> p->age;
    cout << "手机号："; cin >> p->phoneno;
    cout << "微信号："; cin >> p->wechatno;
    cout << "------------------------" << endl;
    return true;
} // 修改第pos个节点，首节点记为第1个节点

PNODE lookup_list(PNODE pHead, string s) {
    PNODE p = pHead;
    int i = 0;
    while (p != NULL) {
        if ((string) p->name == s || (string) p->sex == s || (string) p->phoneno == s || (string) p->wechatno == s ||
            to_string(p->age) == s) {
            cout << "查找到 " << s << " 出现在第 " << i << " 个节点" << endl;
            return p; // 查找到，返回节点地址
        }
        i++;
        p = p->pNext;
    }
    return NULL; // 没有查找到，返回NULL
} // 查找含有“xxx”信息的节点位置