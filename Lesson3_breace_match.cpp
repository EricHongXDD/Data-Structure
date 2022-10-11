/*
 * �����ܣ����ʽ���������
 * �汾�ţ�2022-10-10
 * ���뻷����MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>
#include <cstring>

typedef struct NODE{
    char ch;
    struct NODE * pNext;
}*PNODE, NODE;
typedef struct {
    PNODE pTop;
    PNODE pBottom;
}*PSTACK, STACK;

PSTACK init_stack(); // ��ʼ��ջ
bool push_stack(PSTACK, char); // ѹջ
bool pop_stack(PSTACK, char *); // ��ջ
bool is_empt(PSTACK); // �ж�ջ�Ƿ�Ϊ��
bool is_left(char); // �ж��Ƿ�Ϊ������
bool is_right(char); // �ж��Ƿ�Ϊ������
bool is_rmatch(PSTACK, char); // �ж������� �Ƿ�� ������ƥ��
void solve(PSTACK, char*); // �㷨
using namespace std;

int main() {
    int t; cout << "�м������ʽ���жϣ�"; cin >> t;
    for (int i = 0; i < t; ++i) {
        PSTACK ps = init_stack();
        string s; cout << "������ʽ" << i+1; cin >> s;
        char *c = (char*)malloc(size(s));
        strcpy(c,s.c_str());
        solve(ps,c);
    }
    return 0;
}

PSTACK init_stack(){
    PSTACK ps = (PSTACK)malloc(sizeof(STACK));
    ps->pBottom = (PNODE)malloc(sizeof(NODE));
    ps->pBottom->pNext = nullptr;
    ps->pTop = ps->pBottom;
    return ps;
}
bool push_stack(PSTACK ps, char ch){
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->pNext = ps->pTop;
    pNew->ch = ch;
    ps->pTop = pNew;
    return true;
}
bool pop_stack(PSTACK ps, char * ch){
    if (!is_empt(ps)){
        *ch = ps->pTop->ch;
        PNODE p = ps->pTop;
        ps->pTop = ps->pTop->pNext;
        free(p);
        p = nullptr;
        return true;
    }
    else
        return false;
}
bool is_empt(PSTACK ps){
    if (ps->pTop == ps->pBottom)
        return true;
    else
        return false;
}
bool is_left(char ch){
    switch (ch){
        case '{':
        case '(':
        case '[':
            return true;
        default:
            return false;
    }
}
bool is_right(char ch){
    switch (ch) {
        case '}':
        case ')':
        case ']':
            return true;
        default:
            return false;
    }
}
bool is_rmatch(PSTACK ps, char ch){
    char match_ch = ps->pTop->ch;
    bool flag1 = false, flag2 = false, flag3 = false;
    if (ch == '}' && match_ch == '{') flag1 = true;
    if (ch == ']' && match_ch == '[') flag2 = true;
    if (ch == ')' && match_ch == '(') flag3 = true;
    if (flag1 || flag2 || flag3) return true;
    else return false;
}

void solve(PSTACK ps, char* s){
    char temp;
    for (int i = 0; s[i] != '\0'; ++i) {
        char ch = s[i];
        if (is_left(ch))
            push_stack(ps,s[i]);
        else if (is_right(ch))
            if (is_rmatch(ps,ch))
                pop_stack(ps,&temp);
            else{
                cout << s << " �����" << endl;
                return;
            }
        else
            continue;
    }
    if (is_empt(ps))
        cout << s << " ���" << endl;
    else
        cout << s << " �����" << endl;
}