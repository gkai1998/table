#include "Table.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include "bpt.h"
#include "predefined.h"
using namespace std;
using namespace bpt;
Table::Table(int c,int primaryindex):index("data/indexfile",false)
{
    // 随机生成文件名
    column = c;
    // srand(time(0));
    /*
    int length=5;
    for(int i=0;i<length;i++){
        filename[i]=rand()%('z'-'a'+1)+'a';
    }
    filename[5]='\0';
    */
    fd = open(filename, O_RDWR | O_CREAT);
    primaryIndex=primaryindex;
    // cout<<"size:"<<sizeof(int64_t)<<endl; size=8
}
Table::~Table()
{
    close(fd);
}

void Table::writeToFileEnd(int fd, int64_t *buf)
{
    bpt::value_t position =lseek(fd, 0, SEEK_END);
    bpt::key_t key(buf[primaryIndex]);
    int k=index.insert(key,position);
    for (int i = 0; i < column; i++)
    {
        if (write(fd, buf + i, 8) == -1)
        {
            cout << "write  buf[" << i << "] error" << endl;
            cout << strerror(errno) << endl;
        }
        else
        {
            cout << strerror(errno) << endl;
        }
    }
}

void Table::findColumnData(value_t data)
{
    off64_t fileEnd = lseek(fd, 0, SEEK_END);
    off64_t curPosition = lseek(fd, 0, SEEK_SET);
    int64_t data1;
    off64_t dataposition;
    // cout<<curPosition<<endl;
    // cout<<fileEnd<<endl;
    if(&index!=NULL){
        bpt::key_t key(data);
    if(index.search(data,&dataposition)==0)
        curPosition = printdata(fd,dataposition);
    else
        cout<<"没找到"<<data<<endl; 
    }  
    
    else{
    while (curPosition < fileEnd)
    {
        curPosition = lseek(fd, 8 * primaryIndex, SEEK_CUR);
        int64_t temp;
        if (read(fd, &temp, 8) == -1)
        {
            cout << "在遍历寻找列数据过程中读出错" << endl;
        }
        else
        {
            if (temp == data)
            {
                curPosition = lseek(fd, -8 * (primaryIndex + 1), SEEK_CUR);
                // cout<<curPosition<<endl;
                curPosition = printdata(fd, curPosition);
                // sleep(2);
                break;
            }
            else
            {
                curPosition = lseek(fd, 8 * (column - primaryIndex - 1), SEEK_CUR);
            }
        }
    }

    }
    
}
off64_t Table::printdata(int fd, off64_t curposition)
{
    lseek(fd, curposition, SEEK_SET);
    int64_t data;
    for (int i = 0; i < column; i++)
    {
        if (read(fd, &data, 8) != -1)
            cout << data << " ";
        else
            cout << "printdata error";
    }
    cout << endl;
    return lseek(fd, 0, SEEK_CUR);
}

void Table::findRangeData(int64_t min,int64_t max){
    off64_t fileEnd = lseek(fd, 0, SEEK_END);
    off64_t curPosition = lseek(fd, 0, SEEK_SET);
    int64_t data1;
    // cout<<curPosition<<endl;
    // cout<<fileEnd<<endl;
    if((&index)!=NULL){
        bpt::key_t key1(min);
        bpt::key_t key2(max-2);
        bpt::value_t values[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        int t=index.search_range(&key1,key2,values,10);
        if(t>10){
            cout<<"检索数据超过10条,这里只显示10条"<<endl;
        }
        int i=0;
        while(values[i++]!=-1){
            printdata(fd,values[i]);
            cout<<endl;
        }
    cout<<endl;
    }
    else{
    while (curPosition < fileEnd)
    {
        curPosition = lseek(fd, 8 * primaryIndex, SEEK_CUR);
        int64_t temp;
        if (read(fd, &temp, 8) == -1)
        {
            cout << "在遍历寻找列数据过程中读出错" << endl;
        }
        else
        {
            if (temp>=min&&temp<=max)
            {
                curPosition = lseek(fd, -8 * (primaryIndex + 1), SEEK_CUR);
                // cout<<curPosition<<endl;
                curPosition = printdata(fd, curPosition);
                // sleep(2);
            }
            else
            {
                curPosition = lseek(fd, 8 * (column - primaryIndex - 1), SEEK_CUR);
            }
        }
    }
    }
}