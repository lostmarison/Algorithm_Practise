```cpp
#pragma once
#include <iostream>
#include <cstring>
using namespace std;

class Mat
{
private:
    double **pp_Data;
    int R, C;

public:
    Mat();                                             // 1.默认构造函数(全零数据)
    Mat(int r, int c);                                 // 2.带参构造函数1(全零数据)
    Mat(double *p, int r, int c);                      // 3.带参构造函数2
    Mat(double **pp, int r, int c);                    // 4.带参构造函数3
    Mat(const Mat &m, int r1, int c1, int r2, int c2); // 5.带参构造函数4(子数据)
    Mat(Mat &m);                                       // 6.1拷贝构造函数

    void destroy();                       // 7.释放内存，指针成员赋为nullptr
    void recreate(int r, int c);          // 8.重新分配内存
    void load(double **pp, int r, int c); // 9.载入数据1
    void load(const Mat &m);              // 10.载入数据2

    bool isAllocated();  // 11.判断当前对象是否被分配堆内存
    double *convertTo(); // 12.将当前对象数据转换为数组并返回

    Mat clone();                                   // 13.克隆当前对象
    Mat GetSubMat(int r1, int c1, int r2, int c2); // 14.获取子数据
    Mat getRow(int r);                             // 15.将当前对象指定行作为数组返回
    Mat getCol(int c);                             // 16.将当前对象指定列作为数组返回
    Mat diag();                                    // 17.获取对角线组成的数组
    Mat eye(int n);                                // 18.获取单位数据
    Mat ones(int r, int c);                        // 19.获取全1数据

    void setRow(double *p, int r); // 20.修改指定行
    void setCol(double *p, int c); // 21.修改指定列

    int Rows() { return R; } // 22.获取行数
    int Cols() { return C; } // 23.获取列数

    void copyTo(Mat &m);                                 // 24.将当前对象复制到m
    void copyTo(Mat &m, int r1, int c1, int r2, int c2); // 25.将当前对象的指定范围数据复制到m

    double sum();                               // 26.获取当前对象所有数据和
    double sum(int r1, int c1, int r2, int c2); // 27.获取当前对象指定范围数据和
    double *sumInRow();                         // 28.获取每行和组成的数组
    double *sumInCol();                         // 29.获取每列和组成的数组

    double get(int r, int c) { return pp_Data[r][c]; }
    void set(double data, int r, int c) { pp_Data[r][c] = data; }

    Mat inverse(); // 32.获取当前对象的转置

    Mat plus(const Mat &m);  // 33.求和
    Mat minus(const Mat &m); // 34.求差
    Mat mult(const Mat &m);  // 35.求乘积（按元素）
    Mat div(const Mat &m);   // 36.求商（按元素）

    bool same(const Mat &m); // 37.判断数据相等

    Mat matchInRow(const Mat &m); // 38.行拼接数组
    Mat matchInCol(const Mat &m); // 39.列拼接数组

    Mat &operator=(const Mat &m); // 40.赋值号重载函数
    void print();
};
```

```cpp
#include "stdafx.h"
#include "Mat.h"

//分配内存
double **create(int r,int c)
{
    double **pp=new double*[r];
    for(int i=0;i<r;i++)
        pp[i]=new double[c];
    return pp;
}

//1.默认构造函数
Mat::Mat()
{
    R=C=0;
    pp_Data=nullptr;
}

//2.带参构造函数1(全零数据)
Mat::Mat(int r,int c):R(r),C(c)
{
    pp_Data=create(R,C);
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            pp_Data[i][j]=0;
}

//3.带参构造函数2
Mat::Mat(double *p, int r, int c)
{
    pp_Data=create(R,C);
    int index=0;
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            pp_Data[i][j]=p[index++];
}

//4.带参构造函数3
Mat::Mat(double **pp, int r, int c)
{
    this->load(pp,r,c);
}

//5.带参构造函数4(子数据)
Mat::Mat(const Mat &m, int r1, int c1, int r2, int c2)
{
    this->R=r2-r1+1;
    this->C=c2-c1+1;
    pp_Data=create(R,C);
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            pp_Data[i][j]=m.pp_Data[i+r1][j+c1];
}

//6.拷贝构造函数
Mat::Mat(Mat &m)
{
    this->pp_Data=nullptr;
    this->load(m);
}

//7.释放内存，指针成员赋为nullptr
void Mat::destroy()
{
    if(pp_Data!=nullptr){
        for(int i=0;i<R;i++)
            if(pp_Data[i]!=nullptr){
                delete[] pp_Data[i];
                pp_Data[i]=nullptr;
            }
            delete[] pp_Data;
            pp_Data=nullptr;
    }
    R=C=0;
}

//8.重新分配内存
void Mat::recreate(int r,int c)
{
    this->destroy();
    this->R=r;
    this->C=c;
    pp_Data=create(R,C);
}

//9.载入数据1
void Mat::load(double **pp,int r,int c)
{
    recreate(r,c);
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            pp_Data[i][j]=pp[i][j];
}

//10.载入数据2
void Mat::load(const Mat &m)
{
    recreate(m.R,m.C);
    this->load(m.pp_Data,m.R,m.C);
}

//11.判断当前对象是否被分配堆内存
bool Mat::isAllocated()
{
    return pp_Data != nullptr;
}

//12.将当前对象数据转换为数组并返回
double *Mat::convertTo()
{
    double *arr=new double[R*C];
    int index=0;
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            arr[index++]=pp_Data[i][j];
    return arr;
}

//13.克隆当前对象
Mat Mat::clone()
{
    return Mat(*this);
}

//14.获取子数据
Mat Mat::GetSubMat(int r1, int c1, int r2, int c2)
{
    return Mat(*this, r1, c1, r2, c2);
}

//15.将当前对象指定行作为数组返回
Mat Mat::getRow(int r)
{
    return Mat(*this,r,0,r,C-1);
}

//16.将当前对象指定列作为数组返回
Mat Mat::getCol(int c)
{
    return Mat(*this,0,c,R-1,c);
}

//17.获取对角线组成的数组
Mat Mat::diag()
{
    Mat arr(1, min(R, C));
    for (int i = 0; i < min(R, C); i++)
        arr.pp_Data[0][i] = pp_Data[i][i];
    return arr;
}

//18.获取单位数据
Mat Mat::eye(int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                pp_Data[i][j] = 1;
            else
                pp_Data[i][j] = 0;
        }
    return *this;
}

//19.获取全1数据
Mat Mat::ones(int R, int C)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            pp_Data[i][j] = 1;
    return *this;
}

//20.修改指定行
void Mat::setRow(double *p, int r)
{
    for (int j = 0; j < C; j++)
        pp_Data[r][j] = p[j];
}

//21.修改指定列
void Mat::setCol(double *p, int c)
{
    for (int i = 0; i < R; i++)
        pp_Data[i][c] = p[i];
}

//24.将当前对象复制到m
void Mat::copyTo(Mat &m)
{
    m.recreate(R,C);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            m.pp_Data[i][j] = pp_Data[i][j];
}

//25.将当前对象的指定范围数据复制到m
void Mat::copyTo(Mat &m, int r1, int c1, int r2, int c2)
{
    Mat subMat = GetSubMat(r1, c1, r2, c2);
    subMat.copyTo(m);
}

//26.获取当前对象所有数据和
double Mat::sum()
{
    double sum = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            sum += pp_Data[i][j];
    return sum;
}

//27.获取当前对象指定范围数据和
double Mat::sum(int r1, int c1, int r2, int c2)
{
    double sum = 0;
    for (int i = r1; i <= r2; i++)
        for (int j = c1; j <= c2; j++)
            sum += pp_Data[i][j];
    return sum;
}

//28.获取每行和组成的数组
double *Mat::sumInRow()
{
    double *arr = new double[R];
    for (int i = 0; i < R; i++)
    {
        arr[i] = 0;
        for (int j = 0; j < C; j++)
            arr[i] += pp_Data[i][j];
    }
    return arr;
}

//29.获取每列和组成的数组
double *Mat::sumInCol()
{
    double *arr = new double[C];
    for (int j = 0; j < C; j++)
    {
        arr[j] = 0;
        for (int i = 0; i < R; i++)
            arr[j] += pp_Data[i][j];
    }
    return arr;
}

//32.转置
Mat Mat::inverse()
{
    Mat arr(C, R);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            arr.pp_Data[j][i] = pp_Data[i][j];
    return arr;
}

//33.求和
Mat Mat::plus(const Mat &m)
{
    for (int i = 0; i < min(R, m.R); i++)
        for (int j = 0; j < min(C, m.C); j++)
            pp_Data[i][j] += m.pp_Data[i][j];
    return *this;
}

//34.求差
Mat Mat::minus(const Mat &m)
{
    for (int i = 0; i < min(R, m.R); i++)
        for (int j = 0; j < min(C, m.C); j++)
            pp_Data[i][j] -= m.pp_Data[i][j];
    return *this;
}

//35.求乘积（按元素）
Mat Mat::mult(const Mat &m)
{
    for (int i = 0; i < min(R, m.R); i++)
        for (int j = 0; j < min(C, m.C); j++)
            pp_Data[i][j] *= m.pp_Data[i][j];
    return *this;
}

//36.求商（按元素）
Mat Mat::div(const Mat &m)
{
    for (int i = 0; i < min(R, m.R); i++)
        for (int j = 0; j < min(C, m.C); j++)
        {
            pp_Data[i][j] /= m.pp_Data[i][j];
        }

    return *this;
}

//37.判断数据是否相等
bool Mat::same(const Mat &m)
{
    if (R != m.R || C != m.C)
        return false;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++)
            if (pp_Data[i][j] != m.pp_Data[i][j]){
                return false;
                break;
            }
    }
    return true;
}

//38.行拼接数组
Mat Mat::matchInRow(const Mat &m)
{
    Mat arr(R, C + m.C);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            arr.pp_Data[i][j] = pp_Data[i][j];
    for (int i = 0; i < R; i++)
        for (int j = C; j < C + m.C; j++)
            arr.pp_Data[i][j] = m.pp_Data[i][j - C];
    return arr;
}

//39.列拼接数组
Mat Mat::matchInCol(const Mat &m)
{
    Mat arr(R + m.R, C);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            arr.pp_Data[i][j] = pp_Data[i][j];
    for (int i = R; i < R + m.R; i++)
        for (int j = 0; j < C; j++)
            arr.pp_Data[i][j] = m.pp_Data[i - R][j];
    return arr;
}

//40.赋值号重载函数
Mat &Mat::operator=(const Mat &m)
{
    load(m);
    return *this;
}

//打印
void Mat::print()
{
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            cout<<pp_Data[i][j]<<" ";
        }
        cout<<endl;
    }
}
```
