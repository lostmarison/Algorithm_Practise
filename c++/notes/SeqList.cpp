#include<iostream>
using namespace std;

//线性表——顺序表(数据一个挨一个存储)
struct SeqList
{
    int *pData;//存储位置的基地址
    int Size;//一段连续的存储空间
    int Len;//实际元素个数，即顺序表的长度
};

//创建一个空顺序表
void Create(SeqList &s)//为什么要&:因为属性被修改了
{
    s.pData=new int[10];//分配动态内存
    s.Size=10;
    s.Len=0;
}

//得到一个空顺序表
SeqList Create()
{
    SeqList s;
    s.pData=new int[10];
    s.Size=10;
    s.Len=0;
    return s;
}

//销毁一个顺序表
void Destory(SeqList &s)
{
    if(s.pData!=nullptr)
    {
        delete s.pData;
        s.pData=nullptr;//空指针，不写会变成野指针
    }
    s.Size=s.Len=0;
}

//把一个数据插入顺序报表
void Insert(SeqList &s,int Pos,int Date)//顺序表，插入的位置，插入的数据
{
    if(s.Size==s.Len)//如果容量满了，扩容
    {
        s.pData=(int *)realloc(s.pData,(s.Size+5)*sizeof(int));//扩充内存，非常耗时，扩一个不划算;扩充多少个字节
        s.Size+=5;
    }

    for(int i=s.Len-1;i>=Pos;i--)//从最后一个数开始一个一个往后移一格
        s.pData[i+1]=s.pData[i];

    s.pData[Pos]=Date;
    s.Len++;//数据个数增加一个
}

//从顺序表中删掉一个数据
void Delete(SeqList &s,int Pos)
{
    for(int i=Pos+1;i<=s.Len-1;i++)//从要删掉数据的位置后那个数据开始一个一个往前移一格
        s.pData[i-1]=s.pData[i];//原先在Pos位置上的数据被“顶掉了”

    s.Len--;//数据个数减少一个
}

//输出数据表中的元素
void Cout(SeqList s)
{
    for(int i=0;i<s.Len;i++)
        cout<<s.pData[i]<<endl;
}

//查找一个数据的下标
int Search(SeqList s,int Data)
{
    int Pos=-1;//说明查找的数据不在数据表中
    for(int i=0;i<s.Len;i++)
        if(s.pData[i]==Data)
        {
            Pos=i;
            break;
        }
    return Pos;
}

//删除指定数据
void DeleteData(SeqList &s,int Data)
{
    int Pos=Search(s,Data);//要删除元素的下标
    if(Pos>=0)//如果比0小说明没有这个数据
        Delete(s,Pos);
}

//统计一个数据表中数据出现的次数
int GetCount(SeqList s,int Data)//不用&，因为不会修改s，只是统计数据
{
    int n=0;
    for(int i=0;i<s.Len;i++)
        if(s.pData[i]==Data)
            n++;
    return n;
}

//把重复数据都删掉
void Unique(SeqList &s)
{
    for(int i=0;i<s.Len;i++)
        if(GetCount(s,s.pData[i])>1)//找出重复的数据
        {
            Delete(s,i);
            i--;
        }
    /*    
        int i=0;
        while(i<s.Len)
        {
            int n=GetCount(s,s.pData[i]);
            if(n>1)
                Delete(s,i);
            else
                i++;
        }
    */
}

int main()
{
    SeqList s=Create();
    for(int i=0;i<20;i++)
        Insert(s,i,i/3);
    Unique(s);
    Cout(s);
    Destory(s);
    return 0;
}