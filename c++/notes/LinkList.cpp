#include<iostream>
using namespace std;
//链表是由一系列结点组成，每个结点包含两个域，数据域和指针域(保存下一个结点的地址)
//头结点不是必须，头结点一般不存放数据；首元结点
//结点（ 一个数据+一个指针(指向下一个结点) )
struct Node
{
    int Data;
    Node *Next;//结点指针
};

//创建空链表
//创建一个空链表其实就是创建一个头指针(H)->头结点(***指向的是结点而不是指针域)
Node *Create()
{
    Node *H=new Node;
    H->Next=nullptr;
    return H;
}

//销毁链表
void Destroy(Node *H)
{
    Node *p;
    while (H)
    {
        p=H->Next;
        delete H;
        H=p;
    }
}

//用一个指针指向结点
Node *MoveTo(Node *H,int Pos)
{
    Node *p=H;
    for(int i=0;i<Pos;i++)
        p=p->Next;
    return p;
}

//给链表插入数据
void Insert(Node *H,int Data,int Pos)
{
    Node *p=new Node;
    p->Data=Data;

    Node *q=MoveTo(H,Pos-1);

    p->Next=q->Next;
    q->Next=p;
}

//头插法输入N个数据(头插法是每次都插入到头结点后)
void Head_Insert(Node *H,int N)
{
    for(int i=1;i<=N;i++){
        Node *p=new Node;//创造一个结点;
        cin>>p->Data;
        p->Next=H->Next;
        H->Next=p;
    }
}

//尾插法给链表插入N个数据
void Tail_Insert(Node *H,int N)
{
    Node *q=H;//先建立一个带头结点和尾指针的单链表
    for(int i=0;i<N;i++){
        Node *p=new Node;//指针p应在循环里，每循环一次创建一个结点
        cin>>p->Data;
        q->Next=p;//把q插入头结点后
        q=p;//p成为新的头结点
    }
    q->Next=nullptr;//修改尾指针
}

//输出一个链表
void Cout(Node *H)
{
    Node *p=H->Next;//p指向第一个结点(头结点下一个结点)；
    while(p!=nullptr)
    {
        cout<<p->Data<<endl;
        p=p->Next;
    }
}

//删除链表中的Pos位置的数据
void Delete(Node *H,int Pos)
{
    Node *q=MoveTo(H,Pos-1);
    Node *p=q->Next;

    q->Next=p->Next;//q->Next=q->Next->Next;
    delete p;
}

/*
void Delete(Node *H,int Pos)
{
    Node *q=MoveTo(H,Pos);
    Node *p=MoveTo(H,Pos-1);

    p->Next=q->Next;
    delete q;
}
*/

//查找重复数据个数
int GetCount(Node *H,int Data)
{
    int n=0;
    Node *p=H->Next;
    while(p!=nullptr)
    {
        if(p->Data==Data)
            n++;
        p=p->Next;
    }
/*    for(Node *p=H->Next;p!=nullptr;p=p->Next)
        if(p->Data==Data)
            n++;
*/
    return n;
}

//查找数据在链表中为第几个
int Search(Node *H,int Data)
{
    int Pos=0;
    for(Node *p=H->Next;p!=nullptr;p=p->Next)
        if(p->Data==Data)
        {
            Pos++;
            break;
        }
        else
            Pos++;
    return Pos;
}

//删除指定数据
void DeleteData(Node *H,int Data)
{
    int Pos=Search(H,Data);
    if(Pos==0)
        return;
    Delete(H,Pos);
}

//删除重复数据
void Unique(Node *H)
{
    Node *p=H;
    while(p->Next!=nullptr)
        if(GetCount(H,p->Next->Data)>1)
            DeleteData(H,p->Next->Data);
        else
            p=p->Next;
}

int main()
{
    Node *H=Create();
     for(int i=0;i<20;i++)
        Insert(H,i/3,i);
    Cout(H);
    Destroy(H);
    return 0;
}