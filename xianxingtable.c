#define MAXSIZE 20 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
typedef   int ElemType;
typedef   int Status;
#define OK 1
#define ERROR 0
/*************************************************************
线性表顺序存储结构的优缺点
优点：
1.不需要为表中元素之间的逻辑关系而增加额外的存储空间
2.可以快速地存取表中任一位置的元素

缺点：
1.插入和删除操作需要移动大量的元素
2.当线性表长度变化比较大的时候，难以确定存储空间的容量
3.造成存储空间的碎片

在插入和删除时，时间复杂度为O(n)
在存读数据时，时间复杂度为O(1)

**************************************************************/
//定义线性表存储结构
typedef struct 
{
    ElemType data[MAXSIZE];//线性表最大存储容量
    int length;//线性表当前长度                               
}SqList;

Status GetElem(SqList L, int i, ElemType *e )
{
    if (L.length == 0 || i<1 || i>L.length)
        return ERROR
    *e = L.data[i-1];
    return OK;
}

//线性表插入,i表示要插入的位置，e表示要插入的元素
Status  ListInsert(SqList *L, int i, ElemType e)
{
    int k;
    if (L->length == MAXSIZE)
        return ERROR;
    if (i<1 || i>L->length)
        return ERROR;
    if (i <= L->length)
    {
        for(k = L->length; k >= i-1; k--)//将i后面的数据全部后移一位
            L->data[k+1] = L->data[k];
    }
    L->data[i-1] = e;
    L->length++;
    return OK;

}

//线性表删除, i表示要删除第i个元素，e返回删除后的值
 Status ListDelete(SqList L, int i, ElemType *e)
 {
    int k;
    if(L->length == 0)
        return ERROR;
    if(i < 1 || i > L->length)
        return ERROR;
    *e = L->data[i-1];//因为实际删除的i元素，数组是以0开始计数，所以要i-1才是要删除的数字
    if(i < L->length )
    {
        for(k = i; k < L->length; k++)
            L->data[k-1] = L->data[k];
    }
    L->length--;
    return OK;

 }

/*************************************************************
 
 从查找数据的时间复杂度来看：
 1.顺序存储结构O(1)
 2.单链表O(n)
 ----------------------------------------
 从插入和删除数据的时间复杂度来看：
 1.顺序存储结构O(n)
 2.单链表O(1)
-----------------------------------------
单链表解决了顺序存储结构中空间碎片化的问题，所以在空间性能上单链表胜出

**************************************************************/
//定义线性表的单链表存储结构
typedef struct Node//定义一个节点结构体，每个节点有自己的存储的数据data和下一个节点的地址next
{
    ElemType data;
    struct Node *next;
}Node;

typedef struct Node *LinkList;

Status GetElem_Node(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;
    p = L->next;
    j = 1;
    while(p && j<i)//*p不为空，且计数器j从1开始遍历到i找目标节点
    {
        p = p->next;
        ++j;
    }
    if (!p || j>i)
        return ERROR;//第i个节点不存在
    *e  = p->data;
    return OK;
}

Status ListNodeInsert(LinkList *L, int i, ElemType e)
{
    int j;
    LinkList p,s;
    p = *L;
    j = 1;
    while(p && j<1)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i)
        return ERROR;//p如果是空那!p就是1，||是或，有1出1，就证明出错了，j>i就证明要找的i不在链表中，已经超出遍历范围
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;//先把p的后置节点地址给新插入的s，也就是p后面那个节点的地址，相当于把s的尾巴连接好
    p->next = s;//现在是s的头和p后置节点相连，把头给连接上了
    return OK;

}


Status ListNodeDelete(LinkList *L, int i, ElemType *e)
{
    int j;
    LinkList p,q;
    p = *L;
    j = 1;
    while(p->next && j<1)//遍历i-1个节点
    {
        p = p->next;
        ++j;
    }
    if(!(p->next) || j>i )// 要检查要删除的i节点存不存在
        return ERROR;
    q = p->next;
    p->next = q->next;
    *e = q->data;

    free(q);
    return OK;
}

//创建一个单链表,使用头插法
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for(i = 0;i<n;i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand()%100+1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

//创建一个单链表，使用尾插法
void CreateListTail(LinkList *L, int n)
{
    LinkList p,r;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;
    for(i = 0; i<n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand()%100+1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

//链表的删除
Status ClearList(LinkList *L)
{
    LinkList p,q;
    p = (*L)->next;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
    return OK;
}
/***************************************
静态链表，没有指针实现链表操作，用数组代替指针

优点：
1.在插入、删除时，只需要修改游标，不需要移动元素，比顺序存储结构要好

缺点：
1.没有解决连续存储分配带来的表长难以确定的问题
2.失去了顺序存储结构随机存储的特性
**************************************/

/***************************************
线性表总结：
线性表有--->顺序存储结构
       ---->链式存储结构

其中链式存储结构有----->单链表
                ------>静态链表
                ------>循环链表
                ------>双向链表

**************************************/


int main(void)
{
    return 0;
}