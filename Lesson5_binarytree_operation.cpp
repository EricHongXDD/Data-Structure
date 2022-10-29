/*
 * 功　能：二叉树的基本操作(包括二叉树的创建、复制、计算二叉树的深度、先根序序列、中根序序列、后根序序列)
 * 版本号：2022-10-13
 * 编译环境：MinGW CLion 2021.2.3(C++17)
*/
#include <iostream>
#include <queue> // 用于广度优先搜索
using namespace std;
typedef struct BTNode{
    char data;
    struct BTNode *pLchild;
    struct BTNode *pRchild;
}BTNODE,*PBTNODE;

PBTNODE InitBTree(); // 初始化一个二叉树，并返回该二叉树根节点的地址
PBTNODE CreateBTree(string,int *); // 创建一个二叉树，string由键盘输入，int为string中元素位置（初始为0），返回该二叉树根节点的地址
void Preordertraverse(PBTNODE); // 先序遍历一个二叉树
void Inordertraverse(PBTNODE); // 中序遍历一个二叉树
void Postordertraverse(PBTNODE); // 后序遍历一个二叉树
int GetDepthWithDFS(PBTNODE); // 用深度优先搜索求解一个二叉树的深度
int GetDepthWithBFS(PBTNODE); // 用广度优先搜索求解一个二叉树的深度
PBTNODE CopyBTree(PBTNODE); // 复制一个二叉树并返回复制好的二叉树根节点的地址

int main() {
    string s; cin >> s;
    int i = 0; // string中元素位置（初始为0)
    PBTNODE pRoot1 = CreateBTree(s,&i);
    PBTNODE pRoot = CopyBTree(pRoot1);
    Inordertraverse(pRoot);
    int depth = GetDepthWithBFS(pRoot);
    cout << depth;
    return 0;
}

PBTNODE InitBTree(){  // 初始化一个二叉树，并返回该二叉树根节点的地址
    auto pRoot = new BTNODE;
    pRoot->data = '\0';
    pRoot->pLchild = nullptr;
    pRoot->pRchild = nullptr;
    return pRoot;
}

PBTNODE CreateBTree(string s,int * pi){ // 创建一个二叉树，string由键盘输入，int为string中元素位置（初始为0），返回该二叉树根节点的地址
    if (s[*pi] == '#'){ // 当字符串中元素为'#'时，返回一个空指针
        ++(*pi);
        return nullptr;
    }
    PBTNODE pRoot = InitBTree(); // 创建一个新二叉树
    pRoot->data = s[*pi]; // 新二叉树的根节点数据域
    ++(*pi);
    pRoot->pLchild = CreateBTree(s,pi); // 创建一个左子树
    pRoot->pRchild = CreateBTree(s,pi); // 创建一个右子树
    return pRoot;
}

void Preordertraverse(PBTNODE pRoot){ // 先序遍历一个二叉树
    if (pRoot == nullptr){
        return;
    }
    cout << pRoot->data;
    Preordertraverse(pRoot->pLchild);
    Preordertraverse(pRoot->pRchild);
}

void Inordertraverse(PBTNODE pRoot){ // 中序遍历一个二叉树
    if (pRoot == nullptr){
        return;
    }
    Inordertraverse(pRoot->pLchild);
    cout << pRoot->data;
    Inordertraverse(pRoot->pRchild);
}

void Postordertraverse(PBTNODE pRoot){ // 后序遍历一个二叉树
    if (pRoot == nullptr){
        return;
    }
    Postordertraverse(pRoot->pLchild);
    Postordertraverse(pRoot->pRchild);
    cout << pRoot->data;
}

int GetDepthWithDFS(PBTNODE pRoot){ // 用深度优先搜索求解一个二叉树的深度
    if (pRoot == nullptr) // 递归到叶子节点的子树不存在时，该子树深度为0，递归结束
        return 0;
    else // 如果叶子结点有子树，其深度为左右子树的深度最大值 + 1
        return max(GetDepthWithDFS(pRoot->pLchild),GetDepthWithDFS(pRoot->pRchild)) + 1;
}

int GetDepthWithBFS(PBTNODE pRoot){ // 用广度优先搜索求解一个二叉树的深度
    if (pRoot == nullptr) // 空树
        return 0;
    queue<PBTNODE> nodeQueue; // 创建一个队列保存节点
    nodeQueue.push(pRoot); // 将根节点入队
    int depth= 0; // 用于存放当前深度
    while (!nodeQueue.empty()){ // 当队列非空时进行访问
        ++depth; // 当前树深度 + 1
        unsigned long long count = 0; // 计数器，用于计数“弹出当前层的所有节点”的操作次数
        unsigned long long size = nodeQueue.size(); // size为队列里的根节点个数
        while (count < size){ // 若队列中有与该叶子节点同一层的节点，则继续取头结点，左右孩子入队
            PBTNODE p = nodeQueue.front(); // 取头结点
            nodeQueue.pop(); // 头结点出队
            count++; // 根节点出队的个数 + 1
            if (p->pLchild != nullptr)
                nodeQueue.push(p->pLchild);
            if (p->pRchild != nullptr)
                nodeQueue.push(p->pRchild);
        }
    }
    return depth;
}

PBTNODE CopyBTree(PBTNODE pRoot){ // 复制一个二叉树并返回复制好的二叉树根节点的地址
    if (pRoot == nullptr){ // 如果是空树，递归结束，返回空指针
        return nullptr;
    }
    else{
        // PBTNODE pNew = new BTNODE; 会报错，因为没有初始化pNew的左右孩子指针域为空，导致遍历的时候会出现野指针
        auto pNew = InitBTree();
        pNew->data = pRoot->data; // 复制根节点的数据
        pNew->pRchild = CopyBTree(pRoot->pRchild); // 递归复制左子树
        pNew->pLchild = CopyBTree(pRoot->pLchild); // 递归复制右子树
        return pNew;
    }
}