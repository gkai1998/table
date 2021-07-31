#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H
#include<stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "bpt.h"
#include "predefined.h"
// typedef struct row
// {
//     int64_t data[100];
// }row;
using namespace std;
using namespace bpt;
class Table {

    private:
    const char *filename="data/datafile";

    public:
    int column;
    int fd;
    int primaryIndex;
    bplus_tree index;

    public:
    Table(int c,int primaryindex);//构造属性列个数为c的表
    ~Table();//关闭表文件
    void writeToFileEnd(int fd,int64_t *buf);//fd:文件标识符 buf:需要写入的数据，加入尾部
    off64_t printdata(int fd,off64_t curposition);//fd:文件标识符 column:属性个树 curposition:从文件偏移量curposition处开始打印，返回读和打印完的文件指针位置
    void findColumnData(value_t data);//寻找属性列col值为data的行数据，并打印
    void findRangeData(int64_t min,int64_t max);//寻找属性列col值大小位于min和max之间的行数据，并打印



};

#endif 