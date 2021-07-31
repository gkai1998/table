#include<iostream>
#include"Table.h"
#include "bpt.h"
#include<iostream>
#include<time.h>
#include "predefined.h"
using namespace bpt;
using namespace std;
using namespace std;
static int prilimirary=0;
int64_t* getdata(int length){
    int64_t *data=(int64_t*)malloc(length*sizeof(int64_t));
    static int prilimirary=0;
    data[0]=prilimirary++;
    for(int i=1;i<length;i++){
        srand(time(0));
        data[i]=rand()%INT64_MAX;
    }
    return data;
}
int main(){
    
    Table ta(100,0);
    // 插入数据
    // for(int i=0;i<10;i++){
    // int64_t *data=getdata(100);
    // ta.writeToFileEnd(ta.fd,data);
    // }


    //查询和范围查询
    ta.findColumnData(7);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    ta.findColumnData(4);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    ta.findColumnData(8);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    ta.findRangeData(55,60);
    cout<<endl;
    cout<<endl;
    cout<<endl;

    return 0;

}