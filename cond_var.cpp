#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

using namespace std;
pthread_cond_t condition;
pthread_mutex_t mutex;
int ii = 0;
#define WAIT_TIME_SECONDS       15
int ret,ret1,cond;

int dosignal;
void *producer(void *arg)
{

  for(;;)
  {
   ret = pthread_mutex_trylock(&mutex); //try to lock mutex
if(ret == 0)  //if locked success then go ahead                            
{
    cout << "producer locked" << endl;
    if(ii < 5 )
    {
      cout << "producer waiting" << endl;
      cond = pthread_cond_wait(&condition,&mutex);
      if(cond == 0)
        {
          cout << "producer unlocked"<<endl;   
          pthread_mutex_unlock(&mutex);
         }
      cout << "after waiting" << endl;
    }
    else 
    {
      cout << "P " << ii << endl;
      ii++;
    }
    cout << "producer mutex Unlocking" << endl;
    pthread_mutex_unlock(&mutex);
    if(ii >= 10)
     {
      return 0;
     } 
   }
  }
}

void * consumer(void *arg)
{

 for(;;)
  {
    ret1 = pthread_mutex_trylock(&mutex); 
  if(ret1 == 0)
   {
    cout << "consumer locked" << endl;

    if(ii >= 5)
    {
      cout << "consumer signal" << endl;
      dosignal =1;

   //  pthread_cond_signal(&condition);
    }
    else{
      cout <<  "C " <<  ii << endl;
      ii++;
    }
    pthread_mutex_unlock(&mutex);
    cout << "consumer unlocked" << endl;

    if(dosignal)
    {

     pthread_cond_signal(&condition);
     return 0;
    }
  // sleep(1);
  //  cout << "consumer unlocked" << endl;
    if(ii >= 10){
      return 0;
      }
    }
  }
}
int main(int argc, char *argv[])
{
  pthread_t proThrHanle, conThrHandle;

  pthread_create(&proThrHanle,NULL,producer,NULL);
  //sleep(1);
  pthread_create(&conThrHandle,NULL, consumer,NULL);

  pthread_join(proThrHanle,NULL);
  pthread_join(conThrHandle,NULL);
}
