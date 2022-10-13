/*
 * 功　能：简单算数表达式求值
 * 版本号：2022-10-14
 * 编译环境：MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>

using namespace std;

// 结构定义：节点
typedef struct Node{
    char data; // 数据域
    struct Node *pNext; // 指针域
}*PNODE,NODE;

// 结构定义：栈
typedef struct Stack{
    PNODE pTop; // 栈顶节点
    PNODE pBottom; // 栈尾节点
}*PSTACK,STACK;

PSTACK init_stack(); // 初始化一个栈
bool is_stack_empty(PSTACK); // 判定栈是否为空
void push_stack(PSTACK,char); // 压栈
bool pop_stack(PSTACK, char*); // 出栈一次，并把出栈的元素存入形参所指向变量中
char * create_list(); // 将算数表达式存入LIST中，并返回LIST第一个字符的地址
int get_priority(char); // 得到运算符的优先级，返回1或2,优先级越高，越早计算
char * to_postfix(PSTACK, PSTACK, char *); // 将中缀表达式转变成后缀表达式
bool number_operation(PSTACK, PSTACK, char); // 遇到操作数的操作
bool operator_operation(PSTACK, PSTACK, char); // 遇到运算符的操作
bool brace_operation(PSTACK, PSTACK, char); // 遇到括号的操作
int calculate_postfix(char *); // 计算后缀表达式

string LIST; // LIST存放算数表达式，以数组形式储存

int main() {
    char *list; // list存放算数表达式的第一个字符的地址
    list = create_list();

    PSTACK pS1 = init_stack(); // 运算符栈pS1
    PSTACK pS2 = init_stack(); // 储存中间结果栈pS2

    list = to_postfix(pS1, pS2, list); // 转换成后缀表达式
    cout << "后缀表达式的结果为" << endl;
    for (int i = 0; list[i] != '\0'; ++i) cout << list[i] << " ";
    cout << endl;

    int res = calculate_postfix(list);
    cout << "运算结果为：" << res << " ";
    return 0;
}

PSTACK init_stack(){
    auto pStack = (PSTACK)malloc(sizeof(STACK));
    pStack->pTop = (PNODE)malloc(sizeof(NODE)); // 在pStack这个栈内，与其头节点分配内存空间
    if (pStack->pTop == nullptr){
        cout << "动态内存分配失败";
        exit(-1);
    }
    pStack->pTop->pNext = nullptr; // 头结点pTop的指针域为空，因为他是栈内最后一个节点
    pStack->pBottom = pStack->pTop; // 初始时，只有一个节点，让尾结点就是头结点
    return pStack;
}

bool is_stack_empty(PSTACK pS){
    if (pS->pTop == pS->pBottom)
        return true;
    else
        return false;
}

void push_stack(PSTACK pS, char data){
    auto pNew = (PNODE)malloc(sizeof(NODE)); // pNew为要压入的新节点
    pNew->data = data;
    pNew->pNext = pS->pTop; // 压入的新节点的指针域指向原先的Top节点
    pS->pTop = pNew; // 原先的Top节点指针域指向压入的新节点
}

bool pop_stack(PSTACK pS, char* pData){
    if (is_stack_empty(pS))
        return false;
    else
    {
        *pData = pS->pTop->data;
        PNODE r = pS->pTop;
        pS->pTop = r->pNext;
        free(r);
        r = nullptr; // r=nullptr是因为free（r）只是把指针r所指的变量释放了，但r本身还存着地址，需要使r为空指针让他不存任何地址
        return true;
    }
}

bool number_operation(PSTACK pS1, PSTACK pS2, char list){
    if (isdigit(list)){ // 遇到操作数时，压入s2；
        push_stack(pS2,list);
        return true;
    }
    else
        return false;
}

bool operator_operation(PSTACK pS1, PSTACK pS2, char list){
    char *pData = (char*)malloc(sizeof(char)); // 用于存放出栈的节点数据域
    if (list == '+' || list == '-' || list == '*' || list == '/'){ // 遇到运算符时，比较其与s1栈顶运算符的优先级：
        if (is_stack_empty(pS1) || pS1->pTop->data == '(' || get_priority(list) > get_priority(pS1->pTop->data)){ // 如果s1为空，或栈顶运算符为左括号“（” ，或优先级比栈顶运算符高,则直接将此运算符入栈；
            push_stack(pS1,list);
        }
        else{ // 将s1栈顶的运算符弹出并压入到s2中，再次转到4.1步骤与s1中新的栈顶运算符相比较；
            pop_stack(pS1,pData); // 将s1栈顶的运算符弹出
            push_stack(pS2,*pData); // 将s1栈顶的运算符压入到s2中
            operator_operation (pS1,pS2,list); // 再次转到4.1步骤与s1中新的栈顶运算符相比较
        }
        return true;
    }
    else
        return false;
}

bool brace_operation(PSTACK pS1, PSTACK pS2, char list){
    if (list == '('){ // 如果时左括号“（” ，则直接压入s1；
        push_stack(pS1,list);
        return true;
    }
    else if (list == ')'){ // 如果是右括号“）” ，则依次弹出s1栈顶的运算符，并压入s2，直到遇到左括号为止，此时将这一对括号丢弃;
        while (pS1->pTop->data != '('){ // 直到遇到左括号为止
            char *pData = (char*)malloc(sizeof(char));
            pop_stack(pS1,pData); // 依次弹出s1栈顶的运算符
            push_stack(pS2,*pData); // 压入s2
        }
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS1,pData); // 将这一对括号丢弃
        return true;
    }
    else {
        return false;
    }

}

// 1. 将字符串转化为中缀表达式，并存入到LIST中
char * create_list(){
    cin >> LIST;
    return &LIST[0];
}

// 2. 得到运算符优先级
int get_priority(char list){
    int priority = 0;
    switch(list){
        case '+':
        case '-':
            priority = 1;
            break;
        case '*':
        case '/':
            priority = 2;
            break;
        default:
            cout << "运算符错误" << endl;
            exit(-1);
    }
    return priority;
}

// 3. 将中缀表达式转换为后缀表达式，并存入到LIST中
char * to_postfix(PSTACK pS1, PSTACK pS2, char * list){
    for (int i = 0; list[i] != '\0'; ++i){ // 循环遍历中序表达式,直到表达式的最右边
        if (number_operation(pS1, pS2, list[i])) continue;
        if (operator_operation(pS1, pS2, list[i])) continue;
        if (brace_operation(pS1, pS2, list[i])) continue;
    }
    while (!is_stack_empty(pS1)){ // 当s1不为空，将s1中剩余元素依次弹出并压入s2
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS1,pData); // 依次弹出s1栈顶的运算符
        push_stack(pS2,*pData); // 压入s2
    }
    // 结果为s2的逆序，即把s2依次弹出并压入s1，最后输出s1
    while (!is_stack_empty(pS2)){ // 当s2不为空，将s2中剩余元素依次弹出并压入s1
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS2,pData); // 依次弹出s2栈顶的运算符
        push_stack(pS1,*pData); // 压入s1
    }
    // 依次输出s1至list
    for (int i = 0; !is_stack_empty(pS1); ++i){ // 输出list为后缀表达式
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS1,pData);
        list[i] = *pData;
        list[i+1] = '\0'; // 保证list长度始终是i+1
    }
    return list;
}

int calculate_postfix(char * list){
    PSTACK pS = init_stack(); // 该栈用于计算后缀表达式的值
    for (int i = 0; list[i] != '\0'; ++i) {
        if (isdigit(list[i])){ // 遇到数字时，将数字压入堆栈
            push_stack(pS,list[i]);
        }
        else{ // 遇到运算符时，弹出栈顶的两个数，用运算符对它们做相应的计算并将结果入栈
            char a, b, c; // a,b为栈顶两个数(中间量，为字符型)
            int ta, tb, tc; // a,b为栈顶两个数，c为结果数(结果量，为整型)
            pop_stack(pS,&b); // 弹出栈顶的两个数
            pop_stack(pS,&a); // 弹出栈顶的两个数
            ta = a - '0'; tb = b - '0';
            switch (list[i]){ // 用运算符对它们做相应的计算，结果存储在c中
                case '+':
                    tc = ta + tb;
                    break;
                case '-':
                    tc = ta - tb;
                    break;
                case '*':
                    tc = ta * tb;
                    break;
                case '/':
                    tc = ta / tb ;
                    break;
            }
            c = tc + '0';
            push_stack(pS,c);
        }
    }
    char tres;
    pop_stack(pS,&tres);
    int res = tres - '0';
    return res;
}