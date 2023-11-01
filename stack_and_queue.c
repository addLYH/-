#define MAXSIZE 20 
#define OK 1
#define ERROR 0

#include <stdio.h>
#include <string.h>
#include <unistd.h>
typedef   int ElemType;
typedef int SElemType;
typedef int Status;

//定义栈
typedef struct
{
    SElemType data[MAXSIZE];
    int top;//栈顶指针
}SqStack;

//进栈操作push
Status Push(SqStack *S,SElemType e)
{
    if(S->top == MAXSIZE - 1)
    {
        return ERROR;
    }
    S->top++;
    S->data[S->top] = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e )
{
    if(S->top == -1)
    {
        return ERROR;
    }
    *e = S->data[S->top];//将要删除的栈顶的元素给e
    S->top--;
    return OK;
}

/******************************************************
两栈共享空间结构,前提是两个数据类型相同的栈
*******************************************************/
typedef struct 
{
    SElemType data[MAXSIZE];
    int top1;
    int top2;
}SqDoubleStack;

Status Push(SqDoubleStack *S,SElemType e, int stackNumber)
{
    if(S->top1 + 1 = S->top2)
    {
        return ERROR;
    }
    if(stackNumber == 1)
        S->data[++S->top1]=e;
    else if(stackNumber == 2)
        S->data[--S->top2] = e;
    return OK;
}

Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{


}
/******************************************************
栈的链式结构
LinkStack 是栈的指针结构，存放栈顶指针top，整个栈的长度count
StackNode 是栈的存放数据结构，栈内的数据为data，下一个栈元素地址为next
*******************************************************/
typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack
{
    LinkStackPtr top;
    int count;
}LinkStack;

//S是要传入栈的栈指针，S包含栈的长度和栈顶指针，e是要压入的数据
//先申请一个栈节点的指针位置s来存放新加入的元素，s的尾部要连接之前的栈顶指针
//最后将栈顶指针改为新加入的s，这样栈的压入就完成了
Status Push(LinkStack *S,SElemType e)
{
    LinkStackPtr s =(LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;
    S->top = s;
    S->count++;
    return OK; 
}

Status Pop(LinkStack *S, SElemType *e)
{
    LinkStackPtr p;
    if (StackEmpty(*S))
        return ERROR;
    *e = S->top->data;
    p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
    return OK;
}

/***************************************************************
斐波那契
递归
***************************************************************/
int Fbi(int i)
{
    if(i<2)
        return i == 0 ? 0 : 1;
    return Fbi(i-1) + Fbi(i-2);

}

int main()
{
    int i;
    for(int i = 0; i < 40; i++)
        printf("%d",Fbi(i));
    return 0;
}
/***************************************************************
队列
First in First Out --->FIFO    先进先出

允许插入的一端称为队尾，允许删除的一端称为队头
***************************************************************/
/***************************************************************
抽象数据类型

Data:
元素有相同类型，相邻元素具有前去和后驱关系

operation：
1.InitQueue(*Q)---初始化队列，创建一个空队列
2.DestroyQueue(*Q)销毁队列，如果存在队列Q，则销毁
3.ClearQueue(*Q)清空队列
4.QueueEmpty(Q)判断队列是否为空，是则返回TRUE，否则返回FALSE
5.GetHead(Q,*e)，若队列存在且非空，则用e返回队列Q的元素
6.EnQueue(*Q,e)---若队列Q存在，插入新元素e到队列中，并且成为队尾元素
7.DeQueue(*Q,*e)---删除队列中队头的元素，并且用e返回其值
8.QueueLength(Q)--- 返回队列Q点元素个数
***************************************************************/