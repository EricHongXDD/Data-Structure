/*
 * 功　能：简单算数表达式求值（中缀表达式转后缀表达式）
 * 版本号：2022-10-13
 * 编译环境：MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// 结构定义：节点
typedef struct Node{
    int dataint = 0; // 整形域
    char datachar = 0; // 符号域
    struct Node *pNext = nullptr; // 指针域
}*PNODE,NODE;

// 结构定义：栈
typedef struct Stack{
    PNODE pTop; // 栈顶节点
    PNODE pBottom; // 栈尾节点
}*PSTACK,STACK;

PSTACK init_stack(); // 初始化一个栈
bool is_stack_empty(PSTACK); // 判定栈是否为空
void push_stack(PSTACK,int); // 压栈(整形域)
void push_stack(PSTACK,char); // 压栈(符号域)
bool pop_stack(PSTACK, int*); // 出栈一次，并把出栈的整形元素存入形参所指向变量中
bool pop_stack(PSTACK, char*); // 出栈一次，并把出栈的符号元素存入形参所指向变量中
void traverse(PSTACK); // 遍历栈
PSTACK reverse(PSTACK); // 栈逆序


int get_priority(char); // 得到运算符的优先级，返回1或2,优先级越高，越早计算
bool list_to_stack(PSTACK, const char *); // 将存储中缀表达式的字符串转变成栈
PSTACK to_postfix(PSTACK, PSTACK, PSTACK); // 将中缀表达式转变成后缀表达式
bool number_operation(PSTACK, PSTACK, PNODE); // 遇到操作数的操作
bool operator_operation(PSTACK, PSTACK, PNODE); // 遇到运算符的操作
bool brace_operation(PSTACK, PSTACK, PNODE); // 遇到括号的操作
int calculate_postfix(PSTACK); // 计算后缀表达式


int main() {
    string list; // list为存储中缀表达式的字符串
    cin >> list;

    PSTACK pS1 = init_stack(); // 运算符栈pS1(用于转换后缀表达式)
    PSTACK pS2 = init_stack(); // 储存中间结果栈pS2(用于转换后缀表达式)
    PSTACK pS3 = init_stack(); // 储存中缀表达式栈pS3(用于存放中缀表达式)

    list_to_stack(pS3,list.c_str()); // 将中缀表达式字符串转换到栈内
    pS3 = reverse(pS3); // 将中缀表达式字符串转换到栈内

    PSTACK pS4 = to_postfix(pS1, pS2, pS3); // 转换成后缀表达式
    pS4 = reverse(pS4); // 转换成后缀表达式
    cout << "后缀表达式的结果为：" ; traverse(pS4); cout << endl;

    int res = calculate_postfix(pS4);
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

void push_stack(PSTACK pS,int dataint){
    auto pNew = (PNODE)malloc(sizeof(NODE)); // pNew为要压入的新节点
    pNew->dataint = dataint;
    pNew->datachar = '0';
    pNew->pNext = pS->pTop; // 压入的新节点的指针域指向原先的Top节点
    pS->pTop = pNew; // 原先的Top节点指针域指向压入的新节点
}

void push_stack(PSTACK pS, char datachar){
    auto pNew = (PNODE)malloc(sizeof(NODE)); // pNew为要压入的新节点
    pNew->datachar = datachar;
    pNew->dataint = 0;
    pNew->pNext = pS->pTop; // 压入的新节点的指针域指向原先的Top节点
    pS->pTop = pNew; // 原先的Top节点指针域指向压入的新节点
}

bool pop_stack(PSTACK pS, int* pDataint){
    if (is_stack_empty(pS))
        return false;
    else
    {
        *pDataint = pS->pTop->dataint;
        PNODE r = pS->pTop;
        pS->pTop = r->pNext;
        free(r);
        r = nullptr; // r=nullptr是因为free（r）只是把指针r所指的变量释放了，但r本身还存着地址，需要使r为空指针让他不存任何地址
        return true;
    }
}

bool pop_stack(PSTACK pS, char* pDatachar){
    if (is_stack_empty(pS))
        return false;
    else
    {
        *pDatachar = pS->pTop->datachar;
        PNODE r = pS->pTop;
        pS->pTop = r->pNext;
        free(r);
        r = nullptr; // r=nullptr是因为free（r）只是把指针r所指的变量释放了，但r本身还存着地址，需要使r为空指针让他不存任何地址
        return true;
    }
}

bool list_to_stack(PSTACK pS, const char * list){
    string temp;
    temp = list;
    for (int i = 0; i < temp.length();) {
        if (isdigit(list[i])){
            int j = i;
            int res = 0;
            while (isdigit(list[i])){ // 计数器用于计算符号前有几位数字
                ++i;
            }
            for (; j < i; ++j) {
                int temp = list[j] - '0';
                res+= temp*pow(10,i-j-1);
            }
            push_stack(pS,res);
        }
        else{
            push_stack(pS,list[i]);
            ++i;
        }
    }
    return true;
}

void traverse(PSTACK pS){
    auto pNew = pS->pTop;
    while (pNew != pS->pBottom){
        if (pNew->dataint){
            cout << pNew->dataint << " ";
            pNew = pNew->pNext;
        }
        else{
            cout << pNew->datachar << " ";
            pNew = pNew->pNext;
        }
    }
}

PSTACK reverse(PSTACK pS1){
    PSTACK pS2 = init_stack();
    while (!is_stack_empty(pS1)){ // 当s1不为空，将s1中剩余元素依次弹出并压入s2
        if (pS1->pTop->datachar != '0'){ // 为符号
            char Datachar;
            pop_stack(pS1,&Datachar); // 依次弹出s1栈顶的运算符
            push_stack(pS2,Datachar); // 压入s2
        }
        else{ // 为整形
            int Dataint;
            pop_stack(pS1,&Dataint); // 依次弹出s1栈顶的运算符
            push_stack(pS2,Dataint); // 压入s2
        }
    }
    return pS2;
}

bool number_operation(PSTACK, PSTACK pS2, PNODE pTop){
    if (pTop->dataint){ // 遇到操作数时，压入s2；
        push_stack(pS2,pTop->dataint);
        return true;
    }
    else
        return false;
}

bool operator_operation(PSTACK pS1, PSTACK pS2, PNODE pTop){
    char Datachar = '0';// 用于存放出栈的节点数据域
    if (pTop->datachar == '+' || pTop->datachar == '-' || pTop->datachar == '*' || pTop->datachar == '/'){ // 遇到运算符时，比较其与s1栈顶运算符的优先级：
        if (is_stack_empty(pS1) || pS1->pTop->datachar == '(' || get_priority(pTop->datachar) > get_priority(pS1->pTop->datachar)){ // 如果s1为空，或栈顶运算符为左括号“（” ，或优先级比栈顶运算符高,则直接将此运算符入栈；
            push_stack(pS1,pTop->datachar);
        }
        else{ // 将s1栈顶的运算符弹出并压入到s2中，再次转到4.1步骤与s1中新的栈顶运算符相比较；
            pop_stack(pS1,&Datachar); // 将s1栈顶的运算符弹出
            push_stack(pS2,Datachar); // 将s1栈顶的运算符压入到s2中
            operator_operation (pS1,pS2,pTop); // 再次转到4.1步骤与s1中新的栈顶运算符相比较
        }
        return true;
    }
    else
        return false;
}

bool brace_operation(PSTACK pS1, PSTACK pS2, PNODE pTop){
    if (pTop->datachar == '('){ // 如果时左括号“（” ，则直接压入s1；
        push_stack(pS1,pTop->datachar);
        return true;
    }
    else if (pTop->datachar == ')'){ // 如果是右括号“）” ，则依次弹出s1栈顶的运算符，并压入s2，直到遇到左括号为止，此时将这一对括号丢弃;
        while (pS1->pTop->datachar != '('){ // 直到遇到左括号为止
            char *pDatachar = (char*)malloc(sizeof(char));
            pop_stack(pS1,pDatachar); // 依次弹出s1栈顶的运算符
            push_stack(pS2,*pDatachar); // 压入s2
        }
        char *pDatachar = (char*)malloc(sizeof(char));
        pop_stack(pS1,pDatachar); // 将这一对括号丢弃
        return true;
    }
    else {
        return false;
    }

}


// 2. 得到运算符优先级
int get_priority(char list){
    int priority;
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
PSTACK to_postfix(PSTACK pS1, PSTACK pS2, PSTACK pS3){
    auto pTemp = pS3->pTop;
    while(pTemp != pS3->pBottom){ // 循环遍历中序栈,直到栈底
        if (number_operation(pS1, pS2, pTemp)) {
            pTemp = pTemp->pNext;
            continue;
        }
        if (operator_operation(pS1, pS2, pTemp)) {
            pTemp = pTemp->pNext;
            continue;
        }
        if (brace_operation(pS1, pS2, pTemp)) {
            pTemp = pTemp->pNext;
        }
    }
    while (!is_stack_empty(pS1)){ // 当s1不为空，将s1中剩余元素依次弹出并压入s2
        if (pS1->pTop->datachar != '0'){ // 为符号
            char Datachar;
            pop_stack(pS1,&Datachar); // 依次弹出s1栈顶的运算符
            push_stack(pS2,Datachar); // 压入s2
        }
        else{ // 为整形
            int Dataint;
            pop_stack(pS1,&Dataint); // 依次弹出s1栈顶的运算符
            push_stack(pS2,Dataint); // 压入s2
        }
    }
    return pS2;
}

int calculate_postfix(PSTACK pS4){
    PSTACK pS1 = init_stack(); // 该栈用于计算后缀表达式的值
    while (pS4->pTop != pS4->pBottom){
        if (pS4->pTop->dataint){ // 遇到数字时，将数字压入堆栈
            int temp = 0;
            pop_stack(pS4,&temp);
            push_stack(pS1,temp);
        }
        else{ // 遇到运算符时，弹出栈顶的两个数，用运算符对它们做相应的计算并将结果入栈
            int a = 0, b = 0, c = 0;
            char temp = '0';
            pop_stack(pS1,&b);
            pop_stack(pS1,&a);
            switch (pS4->pTop->datachar){ // 用运算符对它们做相应的计算，结果存储在c中
                case '+':
                    c = a + b;
                    break;
                case '-':
                    c = a - b;
                    break;
                case '*':
                    c = a * b;
                    break;
                case '/':
                    c = a / b ;
                    break;
            }
            push_stack(pS1,c);
            pop_stack(pS4,&temp);
        }
    }
    int res;
    pop_stack(pS1,&res);
    return res;
}
