/*
 * �����ܣ����ʽ���������
 * �汾�ţ�2022-09-29
 * ���뻷����MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

typedef struct node{
    char name[8]; //����
    char sex[3]; // �Ա�
    int age; //����
    char phoneno[12]; // �绰��
    char wechatno[16]; // ΢�ź�
    struct node *pNext; // ָ����
}NODE,*PNODE; // ����������

PNODE create_list(void); // ����һ������
int len_list(PNODE); // ��һ������ĳ��ȣ�ͷ��㣩
void empt_list(PNODE); // ���һ������ͷ��㣩
void destroy_list(PNODE*); // ����һ������ͷ����ַ��ע��Ҫȡ��ַ
PNODE find_pTail(PNODE); // ���������β��㣨ͷ�ڵ㣩
bool add_list(PNODE, int); // �����������n���ڵ㣨ͷ�ڵ�, ������
bool insert_list(PNODE, int); // ��������ĳ���ڵ�ǰ����һ���ڵ㣨ͷ�ڵ�, λ��, ֵ��
void traverse_list(PNODE); // ��������ͷ�ڵ㣩
bool delete_list(PNODE, int); // ɾ����n���ڵ㣬�׽ڵ��Ϊ��1���ڵ㣨ͷ��㣬λ�ã�
bool modify_list(PNODE, int); // �޸ĵ�n���ڵ㣬�׽ڵ��Ϊ��1���ڵ㣨ͷ��㣬λ�ã�
PNODE lookup_list(PNODE, string); // ���Һ��С�xxx����Ϣ�Ľڵ�λ�ã�ͷ��㣬��Ϣ��


int main()
{
    PNODE pHead = create_list();
    int len; cout << "����ҪͨѶ¼�����ݵĸ���" << endl; cin >> len;
    add_list(pHead, len);
    traverse_list(pHead);
    insert_list(pHead,2); traverse_list(pHead);
    delete_list(pHead,3);traverse_list(pHead);
    modify_list (pHead, 2);traverse_list(pHead);
    PNODE l = lookup_list(pHead, "��");
    empt_list(pHead); traverse_list(pHead);
    destroy_list(&pHead); traverse_list(pHead);
    return 0;
}

PNODE create_list(void)
{
    PNODE pHead = (PNODE) malloc(sizeof(NODE));
    if (pHead == NULL){
        cout << "��̬�ڴ����ʧ�ܣ�" << endl;
        exit(-1);
    }
    pHead->pNext = NULL;
    return pHead;
} // ����һ��ͨѶ¼����������ͷ���

PNODE find_pTail(PNODE pHead)
{
    PNODE pTail = pHead;
    while (pTail->pNext != NULL)
    {
        pTail = pTail->pNext;
    }
    return pTail;
} // Ѱ��pHead��ָ��������β��㲢�������ַ

bool add_list(PNODE pHead, int val)
{
    PNODE pTail = find_pTail(pHead);
    for (int i = 0; i < val; ++i) {
        cout << "����Ҫ����ĵ� " << (i+1) << " ������" << endl;
        PNODE pNew = (PNODE) malloc(sizeof(NODE));
        pNew->pNext = NULL;
        cout << "������"; cin >> pNew->name;
        cout << "�Ա�"; cin >> pNew->sex;
        cout << "���䣺"; cin >> pNew->age;
        cout << "�ֻ��ţ�"; cin >> pNew->phoneno;
        cout << "΢�źţ�"; cin >> pNew->wechatno;
        pTail->pNext = pNew;
        pTail = pNew; // ��pTailʼ��ָ�����һ���ڵ�
        cout << "------------------------" << endl;
    }
    return true;
} // ��pHead��ָ���������������val���ڵ�

bool insert_list(PNODE pHead, int pos)
{
    PNODE p = pHead;
    int i = 0;
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (pNew == NULL){
        cout << "��̬�ڴ����ʧ�ܣ�" << endl;
        exit(-1);
    }
    for (; i < pos - 1; ++i) {
        p = p->pNext;
    }
    cout << "����Ҫ�����" << pos << "���ڵ�ǰ�������" << endl;
    cout << "������"; cin >> pNew->name;
    cout << "�Ա�"; cin >> pNew->sex;
    cout << "���䣺"; cin >> pNew->age;
    cout << "�ֻ��ţ�"; cin >> pNew->phoneno;
    cout << "΢�źţ�"; cin >> pNew->wechatno;
    pNew->pNext = p->pNext;
    p->pNext = pNew;
    cout << "�ڵ����ɹ�" << endl;
    cout << "------------------------" << endl;
    return true;
} // ��pHead��ָ������ĵ�pos���ڵ��ǰ�����һ���µĽڵ㣬����pos��ֵ��1��ʼ

void traverse_list(PNODE pHead)
{
    PNODE p = pHead;
    if (p == NULL){
        cout << "�������ڻ�������" << endl;
        cout << "------------------------" << endl;
        return;
    }
    if (p->pNext == NULL){
        cout << "����Ϊ��" << endl;
        cout << "------------------------" << endl;
    }
    else{
        for (int i = 0; p->pNext != NULL; i++){
            p = p->pNext;
            cout << "����ĵ� " << (i+1) << " ������Ϊ��" << endl;
            cout << "����:" << p->name << " ";
            cout << "�Ա�:" << p->sex << " ";
            cout << "����:" << p->age << " ";
            cout << "�ֻ���:" << p->phoneno << " ";
            cout << "΢�ź�:" << p->wechatno << endl;
            cout << "------------------------" << endl;
        }
    }
} // ����ͷ�ڵ�ΪpHead������

int len_list(PNODE pHead)
{
    int i = 0;
    for (PNODE p = pHead; p->pNext != NULL; p = p->pNext) {
        i++;
    }
    return i;
} // ��һ������ĳ���


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
    q = NULL; // �ͷ���q���ڴ�ռ䣬����ָ��q���Ǵ��ڣ�����Ҫ��q=NULL������Ұָ��
} // �������

void destroy_list(PNODE *pHead)
{
    empt_list(*pHead);
    *pHead = NULL;
} // ����һ������

bool delete_list(PNODE pHead, int pos)
{
    PNODE p = pHead;
    for (int i = 1; i < pos; ++i) {
        p = p->pNext;
    } // p Ϊɾ����ǰһ���ڵ�
    PNODE q = p->pNext;
    free(q);
    q = NULL;
    p->pNext = p->pNext->pNext;
    cout << "��ɾ����" << pos << "���ڵ�" << endl;
    cout << "------------------------" << endl;
    return true;
} // ɾ����pos���ڵ㣬�׽ڵ��Ϊ��1���ڵ�

bool modify_list(PNODE pHead, int pos){
    PNODE p = pHead;
    for (int i = 0; i < pos; ++i) {
        p = p->pNext;
    } // p Ϊ�޸ĵĽڵ�
    cout << "����Ҫ�޸ĵĵ�" << pos << "���ڵ������" << endl;
    cout << "������"; cin >> p->name;
    cout << "�Ա�"; cin >> p->sex;
    cout << "���䣺"; cin >> p->age;
    cout << "�ֻ��ţ�"; cin >> p->phoneno;
    cout << "΢�źţ�"; cin >> p->wechatno;
    cout << "------------------------" << endl;
    return true;
} // �޸ĵ�pos���ڵ㣬�׽ڵ��Ϊ��1���ڵ�

PNODE lookup_list(PNODE pHead, string s) {
    PNODE p = pHead;
    int i = 0;
    while (p != NULL) {
        if ((string) p->name == s || (string) p->sex == s || (string) p->phoneno == s || (string) p->wechatno == s ||
            to_string(p->age) == s) {
            cout << "���ҵ� " << s << " �����ڵ� " << i << " ���ڵ�" << endl;
            return p; // ���ҵ������ؽڵ��ַ
        }
        i++;
        p = p->pNext;
    }
    return NULL; // û�в��ҵ�������NULL
} // ���Һ��С�xxx����Ϣ�Ľڵ�λ��