/*
 * 功　能：表达式中括号配对
 * 版本号：2022-10-10
 * 编译环境：MinGW CLion 2021.2.3(C++17)
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

PSTACK init_stack(); // 初始化栈
bool push_stack(PSTACK, char); // 压栈
bool pop_stack(PSTACK, char *); // 出栈
bool is_empt(PSTACK); // 判定栈是否为空
bool is_left(char); // 判定是否为左括号
bool is_right(char); // 判定是否为右括号
bool is_rmatch(PSTACK, char); // 判定右括号 是否和 左括号匹配
void solve(PSTACK, char*); // 算法
using namespace std;

int main() {
    int t; cout << "有几个表达式需判断？"; cin >> t;
    for (int i = 0; i < t; ++i) {
        PSTACK ps = init_stack();
        string s; cout << "输入表达式" << i+1; cin >> s;
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
                cout << s << " 不配对" << endl;
                return;
            }
        else
            continue;
    }
    if (is_empt(ps))
        cout << s << " 配对" << endl;
    else
        cout << s << " 不配对" << endl;
}