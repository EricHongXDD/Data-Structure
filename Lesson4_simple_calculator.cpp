/*
 * �����ܣ����������ʽ��ֵ
 * �汾�ţ�2022-10-14
 * ���뻷����MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>

using namespace std;

// �ṹ���壺�ڵ�
typedef struct Node{
    char data; // ������
    struct Node *pNext; // ָ����
}*PNODE,NODE;

// �ṹ���壺ջ
typedef struct Stack{
    PNODE pTop; // ջ���ڵ�
    PNODE pBottom; // ջβ�ڵ�
}*PSTACK,STACK;

PSTACK init_stack(); // ��ʼ��һ��ջ
bool is_stack_empty(PSTACK); // �ж�ջ�Ƿ�Ϊ��
void push_stack(PSTACK,char); // ѹջ
bool pop_stack(PSTACK, char*); // ��ջһ�Σ����ѳ�ջ��Ԫ�ش����β���ָ�������
char * create_list(); // ���������ʽ����LIST�У�������LIST��һ���ַ��ĵ�ַ
int get_priority(char); // �õ�����������ȼ�������1��2,���ȼ�Խ�ߣ�Խ�����
char * to_postfix(PSTACK, PSTACK, char *); // ����׺���ʽת��ɺ�׺���ʽ
bool number_operation(PSTACK, PSTACK, char); // �����������Ĳ���
bool operator_operation(PSTACK, PSTACK, char); // ����������Ĳ���
bool brace_operation(PSTACK, PSTACK, char); // �������ŵĲ���
int calculate_postfix(char *); // �����׺���ʽ

string LIST; // LIST����������ʽ����������ʽ����

int main() {
    char *list; // list����������ʽ�ĵ�һ���ַ��ĵ�ַ
    list = create_list();

    PSTACK pS1 = init_stack(); // �����ջpS1
    PSTACK pS2 = init_stack(); // �����м���ջpS2

    list = to_postfix(pS1, pS2, list); // ת���ɺ�׺���ʽ
    cout << "��׺���ʽ�Ľ��Ϊ" << endl;
    for (int i = 0; list[i] != '\0'; ++i) cout << list[i] << " ";
    cout << endl;

    int res = calculate_postfix(list);
    cout << "������Ϊ��" << res << " ";
    return 0;
}

PSTACK init_stack(){
    auto pStack = (PSTACK)malloc(sizeof(STACK));
    pStack->pTop = (PNODE)malloc(sizeof(NODE)); // ��pStack���ջ�ڣ�����ͷ�ڵ�����ڴ�ռ�
    if (pStack->pTop == nullptr){
        cout << "��̬�ڴ����ʧ��";
        exit(-1);
    }
    pStack->pTop->pNext = nullptr; // ͷ���pTop��ָ����Ϊ�գ���Ϊ����ջ�����һ���ڵ�
    pStack->pBottom = pStack->pTop; // ��ʼʱ��ֻ��һ���ڵ㣬��β������ͷ���
    return pStack;
}

bool is_stack_empty(PSTACK pS){
    if (pS->pTop == pS->pBottom)
        return true;
    else
        return false;
}

void push_stack(PSTACK pS, char data){
    auto pNew = (PNODE)malloc(sizeof(NODE)); // pNewΪҪѹ����½ڵ�
    pNew->data = data;
    pNew->pNext = pS->pTop; // ѹ����½ڵ��ָ����ָ��ԭ�ȵ�Top�ڵ�
    pS->pTop = pNew; // ԭ�ȵ�Top�ڵ�ָ����ָ��ѹ����½ڵ�
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
        r = nullptr; // r=nullptr����Ϊfree��r��ֻ�ǰ�ָ��r��ָ�ı����ͷ��ˣ���r�������ŵ�ַ����ҪʹrΪ��ָ�����������κε�ַ
        return true;
    }
}

bool number_operation(PSTACK pS1, PSTACK pS2, char list){
    if (isdigit(list)){ // ����������ʱ��ѹ��s2��
        push_stack(pS2,list);
        return true;
    }
    else
        return false;
}

bool operator_operation(PSTACK pS1, PSTACK pS2, char list){
    char *pData = (char*)malloc(sizeof(char)); // ���ڴ�ų�ջ�Ľڵ�������
    if (list == '+' || list == '-' || list == '*' || list == '/'){ // ���������ʱ���Ƚ�����s1ջ������������ȼ���
        if (is_stack_empty(pS1) || pS1->pTop->data == '(' || get_priority(list) > get_priority(pS1->pTop->data)){ // ���s1Ϊ�գ���ջ�������Ϊ�����š����� �������ȼ���ջ���������,��ֱ�ӽ����������ջ��
            push_stack(pS1,list);
        }
        else{ // ��s1ջ���������������ѹ�뵽s2�У��ٴ�ת��4.1������s1���µ�ջ���������Ƚϣ�
            pop_stack(pS1,pData); // ��s1ջ�������������
            push_stack(pS2,*pData); // ��s1ջ���������ѹ�뵽s2��
            operator_operation (pS1,pS2,list); // �ٴ�ת��4.1������s1���µ�ջ���������Ƚ�
        }
        return true;
    }
    else
        return false;
}

bool brace_operation(PSTACK pS1, PSTACK pS2, char list){
    if (list == '('){ // ���ʱ�����š����� ����ֱ��ѹ��s1��
        push_stack(pS1,list);
        return true;
    }
    else if (list == ')'){ // ����������š����� �������ε���s1ջ�������������ѹ��s2��ֱ������������Ϊֹ����ʱ����һ�����Ŷ���;
        while (pS1->pTop->data != '('){ // ֱ������������Ϊֹ
            char *pData = (char*)malloc(sizeof(char));
            pop_stack(pS1,pData); // ���ε���s1ջ���������
            push_stack(pS2,*pData); // ѹ��s2
        }
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS1,pData); // ����һ�����Ŷ���
        return true;
    }
    else {
        return false;
    }

}

// 1. ���ַ���ת��Ϊ��׺���ʽ�������뵽LIST��
char * create_list(){
    cin >> LIST;
    return &LIST[0];
}

// 2. �õ���������ȼ�
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
            cout << "���������" << endl;
            exit(-1);
    }
    return priority;
}

// 3. ����׺���ʽת��Ϊ��׺���ʽ�������뵽LIST��
char * to_postfix(PSTACK pS1, PSTACK pS2, char * list){
    for (int i = 0; list[i] != '\0'; ++i){ // ѭ������������ʽ,ֱ�����ʽ�����ұ�
        if (number_operation(pS1, pS2, list[i])) continue;
        if (operator_operation(pS1, pS2, list[i])) continue;
        if (brace_operation(pS1, pS2, list[i])) continue;
    }
    while (!is_stack_empty(pS1)){ // ��s1��Ϊ�գ���s1��ʣ��Ԫ�����ε�����ѹ��s2
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS1,pData); // ���ε���s1ջ���������
        push_stack(pS2,*pData); // ѹ��s2
    }
    // ���Ϊs2�����򣬼���s2���ε�����ѹ��s1��������s1
    while (!is_stack_empty(pS2)){ // ��s2��Ϊ�գ���s2��ʣ��Ԫ�����ε�����ѹ��s1
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS2,pData); // ���ε���s2ջ���������
        push_stack(pS1,*pData); // ѹ��s1
    }
    // �������s1��list
    for (int i = 0; !is_stack_empty(pS1); ++i){ // ���listΪ��׺���ʽ
        char *pData = (char*)malloc(sizeof(char));
        pop_stack(pS1,pData);
        list[i] = *pData;
        list[i+1] = '\0'; // ��֤list����ʼ����i+1
    }
    return list;
}

int calculate_postfix(char * list){
    PSTACK pS = init_stack(); // ��ջ���ڼ����׺���ʽ��ֵ
    for (int i = 0; list[i] != '\0'; ++i) {
        if (isdigit(list[i])){ // ��������ʱ��������ѹ���ջ
            push_stack(pS,list[i]);
        }
        else{ // ���������ʱ������ջ�����������������������������Ӧ�ļ��㲢�������ջ
            char a, b, c; // a,bΪջ��������(�м�����Ϊ�ַ���)
            int ta, tb, tc; // a,bΪջ����������cΪ�����(�������Ϊ����)
            pop_stack(pS,&b); // ����ջ����������
            pop_stack(pS,&a); // ����ջ����������
            ta = a - '0'; tb = b - '0';
            switch (list[i]){ // �����������������Ӧ�ļ��㣬����洢��c��
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