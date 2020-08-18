//
//  main.cpp
//  alg-cpp
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
//#include <windows.h>
#include <queue>
#include <list>
using namespace std;
int initial_id=0;//全局变量，用于初始化新队列的id值
struct PCB//结构体，包含了一个进程状态的所有信息
{
    int id;//进程表指数
    int needtime;//进程剩余需要占用CPU时间
    int runtime;//进程运行完毕需要占用CPU的时间
    int starttime=0;//进程就绪时间
    int whetherblock;//设定该进程是否会出现阻塞
    int startblock=0;//进程开始运行startblock个时间片后开始阻塞
    int blocktime=0;//进程被阻塞的时间
    int state;//运行 1，就绪 0，阻塞 -1，三种状态
};
class ProcessScheduler//调度进程的类
{
public:
    void CreateProcedureQueue(int flag);
    void CreateProcedureList(int flag);
    void FCFS();
    void SJF();
    void SRT();
    void RR();
    void Display();
private:
    queue<PCB> Queue;
    list<PCB> List;
    int capacity;
};

void ProcessScheduler::CreateProcedureQueue(int flag)//用来创建新的进程（队列）
{
    PCB item;
    item.id=++initial_id;
    item.needtime=rand()%19+1;//取随机数，用来初始化needtime，让每次测试结果都不同
    item.runtime=item.needtime;
    item.state=0;
    item.whetherblock=rand()%2;
    if(item.whetherblock==1)
    {
        item.startblock=rand()%(item.needtime);//这样可以保证阻塞的相对开始时间一定小于进程的运行时间。
        item.blocktime=1;
    }
    else
        item.startblock = item.runtime;
    Queue.push(item);
    cout<<"新进程号:"<<item.id<<" 执行所需时间"<<item.needtime;
    if(flag==1)
    {
        if(item.whetherblock==1)//1代表考虑阻塞
        {
            cout<<" 有阻塞";
            cout<<" 阻塞发生时，进程已运行的时间"<<item.startblock<<'\n';
        }
        else
            cout<<" 无阻塞"<<'\n';
        }
    else
        cout<<'\n';
}
void ProcessScheduler::CreateProcedureList(int flag)//用来创建新的进程（列表）方法类似列表
{
    PCB item;
    item.id=++initial_id;
    item.needtime=rand()%19+1;
    item.runtime=item.needtime;
    item.state=0;
    item.whetherblock=rand()%2;
    if(item.whetherblock==1)
    {
        item.startblock=rand()%(item.needtime);
        item.blocktime=1;
    }
    else
        item.startblock=item.runtime;
    List.push_back(item);
    cout<<"新进程号:"<<item.id<<" 执行所需时间"<<item.needtime;
    if(flag==1)
    {
        if(item.whetherblock==1)
        {
            cout<<" 有阻塞";
            cout<<" 阻塞发生时，进程已运行的时间"<<item.startblock<<'\n';
        }
        else
            cout<<" 无阻塞"<<'\n';
    }
    else
        cout<<'\n';
}
/*
 
 FCFS算法，先来先服务，建立队列，按队列顺序执行即可。
 如果发生了阻塞，把阻塞中的队首扔到队列后面。
 
 */
void ProcessScheduler::FCFS()
{
    int i=0;
    int stime=0;
    int flag=0;
    int count=0;
    cout<<"******************************"<<'\n';
    cout<<"FCFS算法演示(先来先服务算法）"<<'\n';
    cout<<"建立5个进程"<<'\n';
    cout<<"默认这5个进程都已经就绪"<<'\n';
    for(i=0;i<5;i++)
        CreateProcedureQueue(1);
    while(!Queue.empty())
    {
        PCB *p=&Queue.front();
        while(p->needtime>(p->runtime-p->startblock))
        {
            //Sleep(1000);
            stime++;
            cout<<"时间片"<<stime;
            cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
            p->needtime--;
        }
        if(p->needtime==(p->runtime-p->startblock))
        {
            //Sleep(1000);
            if((p->runtime-p->startblock)==0)
                Queue.pop();
            else
            {
                cout<<"进程"<<p->id<<"发生阻塞,默认需要1个时间片进入就绪状态."<<'\n';
                p->needtime--;
                Queue.push(Queue.front());
                Queue.pop();
            }
            
        }
        else if(p->needtime<(p->runtime-p->startblock))
        {
            if((p->runtime-p->startblock)>0)
                p->needtime++;
            // Sleep(1000);
            while(p->needtime>0)
            {
                //Sleep(1000);
                stime++;
                cout<<"时间片"<<stime;
                cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
                p->needtime--;
            }
            Queue.pop();
        }
    }
    initial_id=0;
    cout<<"演示完毕"<<'\n';
    cout<<"******************************"<<'\n';
    Display();
}
/*
 SJF短作业优先，建立链表每次选择needtime最短的运行。
 
 */
void ProcessScheduler::SJF()
{
    int i=0;
    int stime=0;
    cout<<"******************************"<<'\n';
    cout<<"SJF算法演示(短作业优先算法）"<<'\n';
    cout<<"建立5个进程"<<'\n';
    cout<<"不考虑阻塞问题了，因为和上面差不多,偷懒了..."<<'\n';
    for(i=0;i<5;i++)
        CreateProcedureList(0);
    while(!List.empty())
    {
        std::list<PCB>::iterator p=List.begin();
        std::list<PCB>::iterator min=List.begin();
        for(;p!=List.end();++p)
        {
            if(p->needtime<min->needtime)
            {
                min=p;
            }
        }
        while(min->needtime!=0)
        {
            stime++;
            cout<<"时间片"<<stime;
            cout<<" 第"<<min->id<<"号进程运行 "<<'\n';
            min->needtime--;
        }
        List.erase(min);
    }
    initial_id=0;
    cout<<"演示完毕"<<'\n';
    cout<<"******************************"<<'\n';
    Display();
}
/*
 最短剩余算法，每当有新的进程就绪，就重新挑出当前最短剩余时间的进程。
 
 因为不是顺序的方式，所以要用链表
 
 默认的2个时间片插入一个进程，这些默认值都可以修改
 
 */
void ProcessScheduler::SRT()
{
    int i=0;
    int stime=0;
    int a=5;//进程的数量
    int s=2;//为了方便计算。自己默认的每隔s时间插入一个进程
    cout<<"******************************"<<'\n';
    cout<<"SRT算法演示(最短剩余时间算法）"<<'\n';
    cout<<"每隔"<<s<<"个时间片插入一个新进程"<<'\n';
    cout<<"一共插入了"<<a<<"个"<<'\n';
    CreateProcedureList(0);
    a--;
    while(!List.empty())
    {
        std::list<PCB>::iterator p=List.begin();
        std::list<PCB>::iterator min=List.begin();
        if(stime==0)
            for(i=0;i<s;i++)
            {
                stime++;
                cout<<"时间片"<<stime;
                cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
                p->needtime--;
                if(p->needtime==0)
                    List.erase(min);
                
            }
        if(stime%s==0)
        {
            if(a>0)
                CreateProcedureList(0);
            a--;
            for(;p!=List.end();++p)
            {
                if(p->needtime<min->needtime)
                {
                    min=p;
                }
            }
            for(int j=0;j<s;j++)
            {
                stime++;
                cout<<"时间片"<<stime;
                cout<<" 第"<<min->id<<"号进程运行 "<<'\n';
                min->needtime--;
                if(min->needtime==0)
                {
                    List.erase(min);
                    break;
                }
            }
        }
        else if(stime%s!=0)
        {
            
            stime++;
            cout<<"时间片"<<stime;
            cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
            p->needtime--;
            if(min->needtime==0)
                List.erase(min);
        }
        else
            break;
    }
    initial_id=0;
    cout<<"演示完毕"<<'\n';
    cout<<"******************************"<<'\n';
    Display();
}
/*
 
 RR轮转法，每隔一定时间片进行下一个进程的分配
 
 用队列排列这些进程，设定一个计时器，每隔n次就将队列头插到尾上
 
 
 */
void ProcessScheduler::RR()
{
    int i=0;
    int stime=0;
    int temp=0;
    int count;//计数器，表示每隔5个时间片中断一次
    cout<<"******************************"<<'\n';
    cout<<"RR算法演示(轮转算法）"<<'\n';
    cout<<"建立5个进程"<<'\n';
    cout<<"默认每隔5个时间片进行一次轮转"<<'\n';
    for(i=0;i<5;i++)
        CreateProcedureQueue(0);
    while(!Queue.empty())
    {
        PCB *p=&Queue.front();
        for(count=5;count>0;count--)
        {
            if(p->needtime!=0&&count>1)
            {
                
                stime++;
                cout<<"时间片"<<stime;
                cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
                p->needtime--;
            }
            else if(p->needtime!=0&&count==1)
            {
                
                stime++;
                cout<<"时间片"<<stime;
                cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
                p->needtime--;
                Queue.push(Queue.front());
                Queue.pop();
            }
            else if(p->needtime==0&&!Queue.empty())
            {
                
                Queue.pop();
//                if(!Queue.empty())
//                    p=&Queue.front();
//                if(p->needtime!=0)
//                {
//                    stime++;
//                    cout<<"时间片"<<stime;
//                    cout<<" 第"<<p->id<<"号进程运行 "<<'\n';
//                    p->needtime--;
//                }
            }
            
        }
        
    }
    initial_id=0;
    cout<<"演示完毕"<<'\n';
    cout<<"******************************"<<'\n';
    Display();
}
void ProcessScheduler::Display()
{
    int key;
    cout<<"请输入数字选择演示哪个算法"<<'\n';
    cout<<"1：FCFS算法"<<'\n';
    cout<<"2: SJF算法"<<'\n';
    cout<<"3: SRT算法"<<'\n';
    cout<<"4: RR算法"<<'\n';
    cout<<"其他任意键: 结束"<<'\n';
    cin>>key;
    switch(key)
    {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            SRT();
            break;
        case 4:
            RR();
            break;
        default:
            break;
    }
}

int main()
{
    
    ProcessScheduler test;
    test.Display();
    return 0;
}

