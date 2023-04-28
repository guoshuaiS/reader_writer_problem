//读者写者问题
//2023.4.28
#include<iostream>
#include<thread>
#include<mutex>
#include<semaphore.h>
using namespace std;
sem_t rCountmutex,wDatamutex,flag;
int rCount=0;
int sums=0; //记录读者总的访问量
int sums_w=0; //限制写者访问量
void writer()
{
    while(sums_w<=1000)
    {
        sem_wait(&flag);
        sem_wait(&wDatamutex);
        sums_w++;
        cout<<"writing ";
        sem_post(&wDatamutex);
        sem_post(&flag);
    }
}
void reader()
{
    while(sums<=1000)
    {
        sem_wait(&flag);
        sem_wait(&rCountmutex);
        if(rCount==0)
        {
            sem_wait(&wDatamutex);
        }
        rCount++;
        sums++;
        sem_post(&rCountmutex);
        sem_post(&flag);
        cout<<"reading ";
        sem_wait(&rCountmutex);
        rCount--;
        if(rCount==0)
        {
            sem_post(&wDatamutex);
        }
        sem_post(&rCountmutex);
    }
}
int main()
{
    sem_init(&rCountmutex,1,1);
    sem_init(&wDatamutex,1,1);
    sem_init(&flag,1,1);
    thread t1(writer),t2(reader);
    t1.join();
    t2.join();
    return 0;
}
